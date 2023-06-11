#include "MainMenuScene.h"

#include "FPSCounter.h"
#include "HighScoreLoader.h"
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

	const auto pFont{ ResourceManager::GetInstance().LoadFont("Retro.otf", 30) };

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
	pName->AddComponent<TextureComponent>();
	pName->AddComponent<TextComponent>()->SetFont(pFont);
	pName->GetComponent<TextComponent>()->SetText("Made by Mendel Debrabandere");
	pName->GetComponent<TextComponent>()->Update();
	pName->GetTransform()->SetWorldPosition(1280.f / 2 - pName->GetComponent<TextureComponent>()->GetTextureSize().x / 2, 750);

	// FPS COUNTER
	const auto pFPSCounter = pGameScene->CreateGameObject();
	pFPSCounter->AddComponent<TextureComponent>();
	pFPSCounter->AddComponent<FPSCounter>();
	pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);


	// SinglePlayer
	const auto pSinglePlayer = pGameScene->CreateGameObject();
	pSinglePlayer->AddComponent<TextureComponent>();
	pSinglePlayer->AddComponent<TextComponent>()->SetFont(pFont);
	pSinglePlayer->GetComponent<TextComponent>()->SetText("Press 1 to start SinglePlayer mode");
	pSinglePlayer->GetComponent<TextComponent>()->SetColor(120, 250, 120);
	pSinglePlayer->GetComponent<TextComponent>()->Update();
	pSinglePlayer->GetTransform()->SetWorldPosition(1280.f / 2 - pSinglePlayer->GetComponent<TextureComponent>()->GetTextureSize().x / 2, 350);

	// Coop
	const auto pCoop = pGameScene->CreateGameObject();
	pCoop->AddComponent<TextureComponent>();
	pCoop->AddComponent<TextComponent>()->SetFont(pFont);
	pCoop->GetComponent<TextComponent>()->SetText("Press 2 to start Co-op mode");
	pCoop->GetComponent<TextComponent>()->SetColor(150, 150, 250);
	pCoop->GetComponent<TextComponent>()->Update();
	pCoop->GetTransform()->SetWorldPosition(1280.f / 2 - pCoop->GetComponent<TextureComponent>()->GetTextureSize().x / 2, 420);

	// versus
	const auto pVersus = pGameScene->CreateGameObject();
	pVersus->AddComponent<TextureComponent>();
	pVersus->AddComponent<TextComponent>()->SetFont(pFont);
	pVersus->GetComponent<TextComponent>()->SetText("Press 3 to start Versus mode");
	pVersus->GetComponent<TextComponent>()->SetColor(250, 150, 80);
	pVersus->GetComponent<TextComponent>()->Update();
	pVersus->GetTransform()->SetWorldPosition(1280.f / 2 - pVersus->GetComponent<TextureComponent>()->GetTextureSize().x / 2, 490);

	//===========================================
	//Highscores
	const auto pHighScore = pGameScene->CreateGameObject();
	pHighScore->AddComponent<TextureComponent>();
	pHighScore->AddComponent<TextComponent>()->SetFont(pFont);
	pHighScore->GetComponent<TextComponent>()->SetText("Highscores:");
	pHighScore->GetComponent<TextComponent>()->SetColor(200, 200, 200);
	pHighScore->GetComponent<TextComponent>()->Update();
	pHighScore->GetTransform()->SetWorldPosition(20, 40);

	HighScoreLoader::LoadHighScores("HighScores.json");
	const auto highScores = HighScoreLoader::GetTopFive();
	for (unsigned int i{}; i < highScores.size(); ++i)
	{
		const auto pScore = pGameScene->CreateGameObject();
		pScore->AddComponent<TextureComponent>();
		pScore->AddComponent<TextComponent>()->SetFont(pFont);
		pScore->GetComponent<TextComponent>()->SetText(highScores[i].first + " - " + std::to_string(highScores[i].second));
		pScore->GetComponent<TextComponent>()->SetColor(200, 200, 200);
		pScore->GetComponent<TextComponent>()->Update();
		pScore->GetTransform()->SetWorldPosition(20, 50.f + 30.f * (static_cast<float>(i) + 1.f));
	}
}
