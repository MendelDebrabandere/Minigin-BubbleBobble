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

	Avatar::CreateAvatar(scene, glm::vec2{ 100,700 }, true, true);
	PlayerMaita::CreateMaita(scene, glm::vec2{ 850,700 });

	//no hud needed in versus
	//HUD::CreateHUD(scene, avatar1->GetComponent<AvatarComponent>());
	//HUD::CreateHUD(scene, avatar2->GetComponent<AvatarComponent>());

	SceneSwapper::GetInstance().m_State = SceneSwapper::GameState::Versus;

	//Start playing the in game music
	dae::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainTheme.mp3", 15, -1);
}
