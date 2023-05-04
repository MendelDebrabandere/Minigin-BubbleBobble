#include "GameSceneCreator.h"

#include "Avatar.h"
#include "FPSCounter.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "LevelLoader.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "TextComponent.h"

using namespace dae;

void GameSceneCreator::CreateGameScene(Scene* pGameScene)
{
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	const auto pBackgroundTexture{ ResourceManager::GetInstance().LoadTexture("background.tga") };
	const auto pLogoTexture{ ResourceManager::GetInstance().LoadTexture("logo.tga") };

	//// BACKGROUND
	//const auto pBG = pGameScene->CreateGameObject();
	//pBG->AddComponent<dae::TextureComponent>()->SetTexture(pBackgroundTexture);

	//// DAE LOGO
	//const auto pLogo = pGameScene->CreateGameObject();
	//pLogo->GetComponent<Transform>()->SetWorldPosition(216, 180);
	//pLogo->AddComponent<TextureComponent>()->SetTexture(pLogoTexture);
	//pLogo->AddComponent<FPSCounter>();

	//// TEXT
	//const auto pTitle = pGameScene->CreateGameObject();
	//pTitle->GetComponent<Transform>()->SetWorldPosition(80, 20);
	//pTitle->AddComponent<TextureComponent>();
	//pTitle->AddComponent<TextComponent>()->SetFont(pFont);
	//pTitle->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");

	//// FPS COUNTER
	//const auto pFPSCounter = pGameScene->CreateGameObject();
	//pFPSCounter->AddComponent<TextureComponent>();
	//pFPSCounter->AddComponent<FPSCounter>();
	//pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);

	//// Create Avatar
	// Avatar::CreateAvatar(pGameScene);

	LevelLoader::LoadLevel(pGameScene, 1);
}
