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

	//Adding it here so the user does not have to enter the engine files in order to change the observers
	Subject::GetInstance().AddObserver<AchievementObserver>();
	Subject::GetInstance().AddObserver<StatsDisplay>();

	// BACKGROUND
	auto go = std::make_shared<GameObject>();
	go->Init();
	go->AddComponent<TextureComponent>()->SetTexture(pBackgroundTexture);
	scene.Add(go);

	// DAE LOGO
	go = std::make_shared<GameObject>();
	go->Init();
	go->GetComponent<Transform>()->SetWorldPosition(216, 180);
	go->AddComponent<TextureComponent>()->SetTexture(pLogoTexture);
	go->AddComponent<FPSCounter>();
	scene.Add(go);

	// TEXT
	go = std::make_shared<GameObject>();
	go->Init();
	go->GetComponent<Transform>()->SetWorldPosition(80, 20);
	go->AddComponent<TextureComponent>();
	const auto pHeaderText{ go->AddComponent<TextComponent>() };
	pHeaderText->SetFont(pFont);
	pHeaderText->SetText("Programming 4 Assignment");
	scene.Add(go);

	// FPS COUNTER
	go = std::make_shared<GameObject>();
	go->Init();
	go->GetComponent<Transform>()->SetWorldPosition(0.0f, 0.0f);
	go->AddComponent<TextureComponent>();
	go->AddComponent<FPSCounter>();
	const auto pText{ go->AddComponent<TextComponent>() };
	pText->SetFont(pFont);
	scene.Add(go);

	// Create the main character gameobject and assign a controller to it
	const auto pCharacter = std::make_shared<GameObject>();
	pCharacter->Init();
	pCharacter->GetComponent<Transform>()->SetWorldPosition(350, 300);
	pCharacter->AddComponent<TextureComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("MainCharacter.png"));
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadUp, 0, InputManager::InputType::Pressed, std::make_unique<MoveUpCommand>(pCharacter.get(), 100.f));
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadDown, 0, InputManager::InputType::Pressed, std::make_unique<MoveDownCommand>(pCharacter.get(), 100.f));
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadLeft, 0, InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pCharacter.get(), 100.f));
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadRight, 0, InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pCharacter.get(), 100.f));
	scene.Add(pCharacter);

	// Create the enemy character gameobject and assign they keyboard to it
	const auto pEnemyRoot = std::make_shared<GameObject>();
	pEnemyRoot->Init();
	pEnemyRoot->GetComponent<Transform>()->SetWorldPosition(0, 300);
	pEnemyRoot->AddComponent<TextureComponent>();
	pEnemyRoot->AddComponent<TextComponent>()->SetFont(pFont);
	pEnemyRoot->AddComponent<HealthComponent>()->SetHealth(100);
	scene.Add(pEnemyRoot);

	const auto pEnemy = std::make_shared<GameObject>();
	pEnemy->Init();
	pEnemy->GetComponent<Transform>()->SetWorldPosition(250, 0);
	pEnemy->AddComponent<TextureComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy.png"));
	InputManager::GetInstance().AddKeyboardCommand('w', InputManager::InputType::Pressed, std::make_unique<MoveUpCommand>(pEnemy.get(), 200.f));
	InputManager::GetInstance().AddKeyboardCommand('s', InputManager::InputType::Pressed, std::make_unique<MoveDownCommand>(pEnemy.get(), 200.f));
	InputManager::GetInstance().AddKeyboardCommand('a', InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pEnemy.get(), 200.f));
	InputManager::GetInstance().AddKeyboardCommand('d', InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pEnemy.get(), 200.f));
	pEnemy->SetParent(pEnemyRoot);
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