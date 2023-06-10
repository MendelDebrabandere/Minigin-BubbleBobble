#include "HighScoreScene.h"

#include <SDL_keycode.h>

#include "FPSCounter.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include "TypingKeyboardComponent.h"

using namespace dae;

void HighScoreScene::Create()
{
	auto& pSceneManager = SceneManager::GetInstance();
	auto* pGameScene = pSceneManager.GetActiveScene();

	InputManager::GetInstance().RemoveAllInputs();

	if (pGameScene)
	{
		pGameScene->RemoveAll();
		pGameScene->SetName("HighScore");
	}
	else
	{
		pGameScene = pSceneManager.CreateScene("HighScore");
	}

	pSceneManager.SetActiveScene(pGameScene);




	//Add a command to go to the menu
	//InputManager::GetInstance().AddKeyboardCommand(SDLK_RETURN, InputManager::InputType::OnDown, std::make_unique<LeaveMenuCommand>())

	const auto pFont{ ResourceManager::GetInstance().LoadFont("Retro.otf", 36) };

	// BubbleBobble logo
	const auto pBG = pGameScene->CreateGameObject();
	const auto pGameLogoTexture{ ResourceManager::GetInstance().LoadTexture("BubbleBobbleLogo.png") };
	pBG->AddComponent<TextureComponent>()->SetTexture(pGameLogoTexture);
	pBG->GetTransform()->SetWorldPosition(1280.f / 2 - pGameLogoTexture->GetSize().x / 2, 20);

	// FPS COUNTER
	const auto pFPSCounter = pGameScene->CreateGameObject();
	pFPSCounter->AddComponent<TextureComponent>();
	pFPSCounter->AddComponent<FPSCounter>();
	pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);

	// Enter your name for your highscore
	const auto pName = pGameScene->CreateGameObject();
	pName->AddComponent<TextureComponent>();
	pName->AddComponent<TextComponent>()->SetFont(pFont);
	pName->GetComponent<TextComponent>()->SetText("Enter the name of your highscore: ");
	pName->GetComponent<TextComponent>()->Update();
	pName->GetTransform()->SetWorldPosition(1280.f / 2 - pName->GetComponent<TextureComponent>()->GetTextureSize().x / 2, 400);

	const auto pTyper = pGameScene->CreateGameObject();
	pTyper->AddComponent<TypingKeyboardComponent>();
	pTyper->AddComponent<TextureComponent>();
	pTyper->AddComponent<TextComponent>()->SetFont(pFont);
	pTyper->GetTransform()->SetWorldPosition(500, 500);

}
