#include "HighScoreScene.h"

#include <SDL_keycode.h>

#include "FPSCounter.h"
#include "InputManager.h"
#include "LeaveHighScoreSceneCommand.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ScoreDisplay.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include "ToggleSoundSysCommand.h"
#include "TypingKeyboardComponent.h"
#include "TextureComponent.h"

using namespace dae;

void HighScoreScene::Create()
{
	auto& pSceneManager = SceneManager::GetInstance();
	auto* pGameScene = pSceneManager.GetActiveScene();

	InputManager::GetInstance().RemoveAllInputs();

	InputManager::GetInstance().AddKeyboardCommand(SDLK_F2, InputManager::InputType::OnDown, std::make_unique<ToggleSoundSysCommand>());

	//Get total highscore
	int totalHighScore{};
	for (auto& go : pGameScene->GetAllObjects())
	{
		const auto scoreDisplay = go->GetComponent<ScoreDisplay>();
		if (scoreDisplay)
		{
			totalHighScore += scoreDisplay->GetScore();
		}
	}


	//clear scene and set up for new one
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


	//CREATE SCENE
	//=============================================
	//Add a command to go to the scene
	InputManager::GetInstance().AddKeyboardCommand(SDLK_RETURN, InputManager::InputType::OnDown, std::make_unique<LeaveHighScoreSceneCommand>(totalHighScore));

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

	// Your Highscore:
	const auto pScore = pGameScene->CreateGameObject();
	pScore->AddComponent<TextureComponent>();
	pScore->AddComponent<TextComponent>()->SetFont(pFont);
	pScore->GetComponent<TextComponent>()->SetText("Total score: " + std::to_string(totalHighScore));
	pScore->GetComponent<TextComponent>()->Update();
	pScore->GetTransform()->SetWorldPosition(1280.f / 2 - pScore->GetComponent<TextureComponent>()->GetTextureSize().x / 2, 350);


	// Enter your name for your highscore
	const auto pName = pGameScene->CreateGameObject();
	pName->AddComponent<TextureComponent>();
	pName->AddComponent<TextComponent>()->SetFont(pFont);
	pName->GetComponent<TextComponent>()->SetText("Enter the name of your highscore: ");
	pName->GetComponent<TextComponent>()->Update();
	pName->GetTransform()->SetWorldPosition(1280.f / 2 - pName->GetComponent<TextureComponent>()->GetTextureSize().x / 2, 400);

	//Input typer
	const auto pTyper = pGameScene->CreateGameObject();
	pTyper->AddComponent<TypingKeyboardComponent>();
	pTyper->AddComponent<TextureComponent>();
	pTyper->AddComponent<TextComponent>()->SetFont(pFont);
	pTyper->GetComponent<TextComponent>()->SetColor(250,50,50);
	pTyper->GetTransform()->SetWorldPosition(500, 500);


	//Cap is at 10 characters
	const auto pCap = pGameScene->CreateGameObject();
	pCap->AddComponent<TextureComponent>();
	pCap->AddComponent<TextComponent>()->SetFont(pFont);
	pCap->GetComponent<TextComponent>()->SetText("Max name length is 10 characters");
	pCap->GetComponent<TextComponent>()->SetColor(150,150,150);
	pCap->GetComponent<TextComponent>()->Update();
	pCap->GetTransform()->SetWorldPosition(1280.f / 2 - pCap->GetComponent<TextureComponent>()->GetTextureSize().x / 2, 700);
}
