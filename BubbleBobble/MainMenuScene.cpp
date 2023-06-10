#include "MainMenuScene.h"

#include "FPSCounter.h"
#include "InputManager.h"
#include "LeaveMenuCommand.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextComponent.h"

using namespace dae;

void MainMenuScene::Create()
{
	auto& pSceneManager = SceneManager::GetInstance();
	auto* pGameScene = pSceneManager.GetActiveScene();

	InputManager::GetInstance().RemoveAllInputs();

	if (pGameScene)
	{
		pGameScene->RemoveAll();
	}
	else
	{
		pGameScene = pSceneManager.CreateScene("MainMenu");
	}

	pSceneManager.SetActiveScene(pGameScene);


	//Add a command to start the game
	InputManager::GetInstance().AddKeyboardCommand(' ', InputManager::InputType::OnDown, std::make_unique<LeaveMenuCommand>());

	const auto pBackgroundTexture{ ResourceManager::GetInstance().LoadTexture("background.tga") };
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	const auto pLogoTexture{ ResourceManager::GetInstance().LoadTexture("logo.tga") };

	// BACKGROUND
	const auto pBG = pGameScene->CreateGameObject();
	pBG->AddComponent<TextureComponent>()->SetTexture(pBackgroundTexture);

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
	pTitle->GetComponent<TextComponent>()->SetText("Press space to start");

	// FPS COUNTER
	const auto pFPSCounter = pGameScene->CreateGameObject();
	pFPSCounter->AddComponent<TextureComponent>();
	pFPSCounter->AddComponent<FPSCounter>();
	pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);

}
