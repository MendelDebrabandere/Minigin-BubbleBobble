#include "GameSceneCreator.h"
#include "FPSCounter.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "TextComponent.h"

using namespace dae;

void GameSceneCreator::CreateGameScene(dae::Scene* pGameScene)
{
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	const auto pBackgroundTexture{ ResourceManager::GetInstance().LoadTexture("background.tga") };
	const auto pLogoTexture{ ResourceManager::GetInstance().LoadTexture("logo.tga") };

	// BACKGROUND
	const auto pBG = pGameScene->CreateGameObject();
	pBG->AddComponent<dae::TextureComponent>()->SetTexture(pBackgroundTexture);

	// DAE LOGO
	const auto pLogo = pGameScene->CreateGameObject();
	pLogo->GetComponent<Transform>()->SetWorldPosition(216, 180);
	pLogo->AddComponent<TextureComponent>()->SetTexture(pLogoTexture);
	pLogo->AddComponent<FPSCounter>();

	// TEXT
	const auto pTitle = pGameScene->CreateGameObject();
	pTitle->GetComponent<Transform>()->SetWorldPosition(80, 20);
	pTitle->AddComponent<TextureComponent>();
	pTitle->AddComponent<TextComponent>()->SetFont(pFont);
	pTitle->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");

	// FPS COUNTER
	const auto pFPSCounter = pGameScene->CreateGameObject();
	//pFPSCounter->GetComponent<Transform>()->SetWorldPosition(0.0f, 0.0f);
	pFPSCounter->AddComponent<TextureComponent>();
	pFPSCounter->AddComponent<FPSCounter>();
	pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);

	// Create the main character gameobject and assign they keyboard to it
	const auto pCharacter = pGameScene->CreateGameObject();
	pCharacter->GetComponent<Transform>()->SetWorldPosition(250, 300);
	pCharacter->AddComponent<TextureComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("MainCharacter.png"));
	InputManager::GetInstance().AddKeyboardCommand('a', InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pCharacter, 200.f));
	InputManager::GetInstance().AddKeyboardCommand('d', InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pCharacter, 200.f));
	pCharacter->AddComponent<HealthComponent>()->SetMaxHealth(100);
	std::cout << "Player 2 uses WASD, 1 to take damage, 2 to increase score.\n";

	//Stat tracker for character
	const auto pCharacterHealthTracker = pGameScene->CreateGameObject();
	pCharacterHealthTracker->GetComponent<Transform>()->SetWorldPosition(0, 150);
	pCharacterHealthTracker->AddComponent<TextureComponent>();
	pCharacterHealthTracker->AddComponent<TextComponent>()->SetFont(pFont);

	const auto pCharacterScoreTracker = pGameScene->CreateGameObject();
	pCharacterScoreTracker->GetComponent<Transform>()->SetWorldPosition(0, 200);
	pCharacterScoreTracker->AddComponent<TextureComponent>();
	pCharacterScoreTracker->AddComponent<TextComponent>()->SetFont(pFont);

	// Create the enemy character gameobject and assign a controller to it
	const auto pEnemy = pGameScene->CreateGameObject();
	pEnemy->GetComponent<Transform>()->SetWorldPosition(350, 300);
	pEnemy->AddComponent<TextureComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy.png"));
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadLeft, 0, InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pEnemy, 100.f));
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadRight, 0, InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pEnemy, 100.f));
	pEnemy->AddComponent<HealthComponent>()->SetMaxHealth(100);
	std::cout << "Player 2 uses controller DPad to move, A to take damage, B to increase score.\n";

	//Stat tracker for enemy
	const auto pEnemyHealthTracker = pGameScene->CreateGameObject();
	pEnemyHealthTracker->GetComponent<Transform>()->SetWorldPosition(0, 350);
	pEnemyHealthTracker->AddComponent<TextureComponent>();
	pEnemyHealthTracker->AddComponent<TextComponent>()->SetFont(pFont);

	const auto pEnemyScoreTracker = pGameScene->CreateGameObject();
	pEnemyScoreTracker->GetComponent<Transform>()->SetWorldPosition(0, 400);
	pEnemyScoreTracker->AddComponent<TextureComponent>();
	pEnemyScoreTracker->AddComponent<TextComponent>()->SetFont(pFont);
}
