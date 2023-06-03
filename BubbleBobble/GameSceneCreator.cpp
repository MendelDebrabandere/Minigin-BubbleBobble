#include "GameSceneCreator.h"

#include "FPSCounter.h"
#include "LevelLoader.h"
#include "NullSoundSystem.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "TextComponent.h"

using namespace dae;

void GameSceneCreator::CreateGameScene(Scene* pGameScene)
{
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	//const auto pBackgroundTexture{ ResourceManager::GetInstance().LoadTexture("background.tga") };
	//const auto pLogoTexture{ ResourceManager::GetInstance().LoadTexture("logo.tga") };

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

	// FPS COUNTER
	const auto pFPSCounter = pGameScene->CreateGameObject();
	pFPSCounter->AddComponent<TextureComponent>();
	pFPSCounter->AddComponent<FPSCounter>();
	pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);


	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "WASD are the current controls\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";

	ServiceLocator::RegisterSoundSystem(new NullSoundSystem());

	ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainTheme.mp3", 15, -1);


	LevelLoader::LoadLevel(pGameScene, 1);
}
