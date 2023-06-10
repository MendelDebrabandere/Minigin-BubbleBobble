#include "MainMenuScene.h"

#include "FPSCounter.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "StartCoopCommand.h"
#include "StartSinglePlayerCommand.h"
#include "StartVersusCommand.h"
#include "TextComponent.h"
#include "Texture2D.h"

using namespace dae;

void MainMenuScene::Create()
{
	auto& pSceneManager = SceneManager::GetInstance();
	auto* pGameScene = pSceneManager.GetActiveScene();

	InputManager::GetInstance().RemoveAllInputs();

	if (pGameScene)
	{
		pGameScene->RemoveAll();
		pGameScene->SetName("MainMenu");
	}
	else
	{
		pGameScene = pSceneManager.CreateScene("MainMenu");
	}
	pSceneManager.SetActiveScene(pGameScene);


	//Add a commands to start the game
	InputManager::GetInstance().AddKeyboardCommand('1', InputManager::InputType::OnDown, std::make_unique<StartSinglePlayerCommand>());
	InputManager::GetInstance().AddKeyboardCommand('2', InputManager::InputType::OnDown, std::make_unique<StartCoopCommand>());
	InputManager::GetInstance().AddKeyboardCommand('3', InputManager::InputType::OnDown, std::make_unique<StartVersusCommand>());

	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };

	// BubbleBobble logo
	const auto pBG = pGameScene->CreateGameObject();
	const auto pGameLogoTexture{ ResourceManager::GetInstance().LoadTexture("BubbleBobbleLogo.png") };
	pBG->AddComponent<TextureComponent>()->SetTexture(pGameLogoTexture);
	pBG->GetTransform()->SetWorldPosition(1280.f/2 - pGameLogoTexture->GetSize().x / 2, 20);

	// DAE LOGO
	const auto pLogo = pGameScene->CreateGameObject();
	const auto pLogoTexture{ ResourceManager::GetInstance().LoadTexture("logo.tga") };
	pLogo->AddComponent<TextureComponent>()->SetTexture(pLogoTexture);
	pLogo->AddComponent<FPSCounter>();
	pLogo->GetTransform()->SetWorldPosition(1280.f / 2 - pLogoTexture->GetSize().x / 2, 680);

	// made by text
	const auto pName = pGameScene->CreateGameObject();
	pName->GetTransform()->SetWorldPosition(390, 750);
	pName->AddComponent<TextureComponent>();
	pName->AddComponent<TextComponent>()->SetFont(pFont);
	pName->GetComponent<TextComponent>()->SetText("Made by Mendel Debrabandere");

	// FPS COUNTER
	const auto pFPSCounter = pGameScene->CreateGameObject();
	pFPSCounter->AddComponent<TextureComponent>();
	pFPSCounter->AddComponent<FPSCounter>();
	pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);


	// SinglePlayer
	const auto pSinglePlayer = pGameScene->CreateGameObject();
	pSinglePlayer->GetTransform()->SetWorldPosition(360, 350);
	pSinglePlayer->AddComponent<TextureComponent>();
	pSinglePlayer->AddComponent<TextComponent>()->SetFont(pFont);
	pSinglePlayer->GetComponent<TextComponent>()->SetText("Press 1 to start SinglePlayer mode");

	// Coop
	const auto pCoop = pGameScene->CreateGameObject();
	pCoop->GetTransform()->SetWorldPosition(405, 420);
	pCoop->AddComponent<TextureComponent>();
	pCoop->AddComponent<TextComponent>()->SetFont(pFont);
	pCoop->GetComponent<TextComponent>()->SetText("Press 2 to start Co-op mode");

	// versus
	const auto pVersus = pGameScene->CreateGameObject();
	pVersus->GetTransform()->SetWorldPosition(400, 490);
	pVersus->AddComponent<TextureComponent>();
	pVersus->AddComponent<TextComponent>()->SetFont(pFont);
	pVersus->GetComponent<TextComponent>()->SetText("Press 3 to start Versus mode");
}
