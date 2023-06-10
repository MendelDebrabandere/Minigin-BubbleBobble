#include "StartVersusCommand.h"


#include "Avatar.h"
#include "HUD.h"
#include "InputManager.h"
#include "LevelLoader.h"
#include "SceneManager.h"
#include "SceneSwapper.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "AvatarComponent.h"
#include "EnemyComponent.h"
#include "PlayerMaita.h"

void StartVersusCommand::Execute()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto scene = sceneManager.GetActiveScene();

	dae::InputManager::GetInstance().RemoveAllInputs();

	//load level
	scene->RemoveAll();
	LevelLoader::LoadLevel(scene, 1, true);
	scene->SetName("1");

	//remove all enemies, since we dont want other enemies in versus mode
	for (auto& go: scene->GetAllObjects())
	{
		if (go->GetComponent<EnemyComponent>())
			go->Destroy();
	}

	auto avatar = Avatar::CreateAvatar(scene, glm::vec2{ 100,700 }, true, true);
	auto maita = PlayerMaita::CreateMaita(scene, glm::vec2{ 850,700 });

	HUD::CreateHUD(scene, avatar->GetComponent<AvatarComponent>(), maita->GetComponent<PlayerMaitaComponent>());

	SceneSwapper::GetInstance().m_State = SceneSwapper::GameState::Versus;

	//Start playing the in game music
	dae::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainTheme.mp3", 15, -1);
}
