#include "HighScoreScene.h"

#include "FPSCounter.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "Texture2D.h"

using namespace dae;

void HighScoreScene::Create()
{
	//auto& pSceneManager = SceneManager::GetInstance();
	//auto* pGameScene = pSceneManager.GetActiveScene();

	//InputManager::GetInstance().RemoveAllInputs();

	//if (pGameScene)
	//{
	//	pGameScene->RemoveAll();
	//}
	//else
	//{
	//	pGameScene = pSceneManager.CreateScene("MainMenu");
	//}

	//pSceneManager.SetActiveScene(pGameScene);


	////Add a command to start the game
	////InputManager::GetInstance().AddKeyboardCommand(' ', InputManager::InputType::OnDown, std::make_unique<LeaveMenuCommand>());

	//const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };

	//// BubbleBobble logo
	//const auto pBG = pGameScene->CreateGameObject();
	//const auto pGameLogoTexture{ ResourceManager::GetInstance().LoadTexture("BubbleBobbleLogo.png") };
	//pBG->AddComponent<TextureComponent>()->SetTexture(pGameLogoTexture);
	//pBG->GetTransform()->SetWorldPosition(1280.f / 2 - pGameLogoTexture->GetSize().x / 2, 20);

	//// FPS COUNTER
	//const auto pFPSCounter = pGameScene->CreateGameObject();
	//pFPSCounter->AddComponent<TextureComponent>();
	//pFPSCounter->AddComponent<FPSCounter>();
	//pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);

}
