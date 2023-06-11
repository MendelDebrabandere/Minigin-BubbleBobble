#include "StartCoopCommand.h"

#include <SDL_keycode.h>


#include "Avatar.h"
#include "HUD.h"
#include "InputManager.h"
#include "LevelLoader.h"
#include "SceneManager.h"
#include "SceneSwapper.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "AvatarComponent.h"
#include "ToggleSoundSysCommand.h"

void StartCoopCommand::Execute()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto scene = sceneManager.GetActiveScene();

	dae::InputManager::GetInstance().RemoveAllInputs();
	dae::InputManager::GetInstance().AddKeyboardCommand(SDLK_F2, dae::InputManager::InputType::OnDown, std::make_unique<ToggleSoundSysCommand>());

	scene->RemoveAll();
	LevelLoader::LoadLevel(scene, 1);
	scene->SetName("1");

	auto avatar1 = Avatar::CreateAvatar(scene, glm::vec2{ 100,700 }, true, true);
	auto avatar2 = Avatar::CreateAvatar(scene, glm::vec2{ 850,700 }, false, false);

	HUD::CreateHUD(scene, avatar1->GetComponent<AvatarComponent>());
	HUD::CreateHUD(scene, avatar2->GetComponent<AvatarComponent>());

	SceneSwapper::GetInstance().m_State = SceneSwapper::GameState::Coop;

	//Start playing the in game music
	dae::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainTheme.mp3", 100, -1);
	dae::ServiceLocator::GetSoundSystem().ToggleMusic(true);
}
