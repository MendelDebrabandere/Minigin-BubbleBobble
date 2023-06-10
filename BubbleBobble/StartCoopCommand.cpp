#include "StartCoopCommand.h"


#include "Avatar.h"
#include "InputManager.h"
#include "LevelLoader.h"
#include "SceneManager.h"
#include "SceneSwapper.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

void StartCoopCommand::Execute()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto scene = sceneManager.GetActiveScene();

	dae::InputManager::GetInstance().RemoveAllInputs();

	scene->RemoveAll();
	LevelLoader::LoadLevel(scene, 1, true);
	scene->SetName("1");

	Avatar::CreateAvatar(sceneManager.GetActiveScene(), glm::vec2{ 100,700 }, true);
	Avatar::CreateAvatar(sceneManager.GetActiveScene(), glm::vec2{ 850,700 }, false);

	SceneSwapper::GetInstance().m_State = SceneSwapper::GameState::Coop;

	//Start playing the in game music
	dae::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainTheme.mp3", 15, -1);
}
