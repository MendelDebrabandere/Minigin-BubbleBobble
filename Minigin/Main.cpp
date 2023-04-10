#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include <iostream>
#include <steam_api.h>

#include "Achievements.h"
#include "FPSCounter.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "HealthComponent.h"
#include "StatsDisplay.h"
#include "Subject.h"

using namespace dae;

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	const auto pBackgroundTexture{ ResourceManager::GetInstance().LoadTexture("background.tga") };
	const auto pLogoTexture{ ResourceManager::GetInstance().LoadTexture("logo.tga") };

	//Adding achievemnt observer
	Subject::GetInstance().AddObserver<AchievementObserver>();

	// BACKGROUND
	const auto pBG = scene.CreateGameObject();
	pBG->AddComponent<TextureComponent>()->SetTexture(pBackgroundTexture);

	// DAE LOGO
	const auto pLogo = scene.CreateGameObject();
	pLogo->GetComponent<Transform>()->SetWorldPosition(216, 180);
	pLogo->AddComponent<TextureComponent>()->SetTexture(pLogoTexture);
	pLogo->AddComponent<FPSCounter>();

	// TEXT
	const auto pTitle = scene.CreateGameObject();
	pTitle->GetComponent<Transform>()->SetWorldPosition(80, 20);
	pTitle->AddComponent<TextureComponent>();
	pTitle->AddComponent<TextComponent>()->SetFont(pFont);
	pTitle->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");

	// FPS COUNTER
	const auto pFPSCounter = scene.CreateGameObject();
	//pFPSCounter->GetComponent<Transform>()->SetWorldPosition(0.0f, 0.0f);
	pFPSCounter->AddComponent<TextureComponent>();
	pFPSCounter->AddComponent<FPSCounter>();
	pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);

	// Create the main character gameobject and assign a controller to it
	const auto pCharacter = scene.CreateGameObject();
	pCharacter->GetComponent<Transform>()->SetWorldPosition(350, 300);
	pCharacter->AddComponent<TextureComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("MainCharacter.png"));
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadUp, 0, InputManager::InputType::Pressed, std::make_unique<MoveUpCommand>(pCharacter, 100.f));
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadDown, 0, InputManager::InputType::Pressed, std::make_unique<MoveDownCommand>(pCharacter, 100.f));
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadLeft, 0, InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pCharacter, 100.f));
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadRight, 0, InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pCharacter, 100.f));

	// Create the enemy character gameobject and assign they keyboard to it
	const auto pEnemy = scene.CreateGameObject();
	pEnemy->GetComponent<Transform>()->SetWorldPosition(250, 300);
	pEnemy->AddComponent<TextureComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy.png"));
	InputManager::GetInstance().AddKeyboardCommand('w', InputManager::InputType::Pressed, std::make_unique<MoveUpCommand>(pEnemy, 200.f));
	InputManager::GetInstance().AddKeyboardCommand('s', InputManager::InputType::Pressed, std::make_unique<MoveDownCommand>(pEnemy, 200.f));
	InputManager::GetInstance().AddKeyboardCommand('a', InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pEnemy, 200.f));
	InputManager::GetInstance().AddKeyboardCommand('d', InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pEnemy, 200.f));
	pEnemy->AddComponent<HealthComponent>()->SetMaxHealth(100);

	const auto pEnemyStatTracker = scene.CreateGameObject();
	pEnemyStatTracker->GetComponent<Transform>()->SetWorldPosition(0, 300);
	pEnemyStatTracker->AddComponent<TextureComponent>();
	pEnemyStatTracker->AddComponent<TextComponent>()->SetFont(pFont);

	auto stats = Subject::GetInstance().AddObserver<StatsDisplay>();
	stats->SetPlayerObject(pEnemy);
	stats->SetTextObject(pEnemyStatTracker);
}

int main(int, char*[]) {
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	std::cout << "Successfully initialized steam." << std::endl;

	Minigin engine("../Data/");
	engine.Run(load);

	SteamAPI_Shutdown();
	return 0;
}