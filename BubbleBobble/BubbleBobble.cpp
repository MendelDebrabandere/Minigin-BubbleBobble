#include "BubbleBobble.h"

#include <random>
#include <ctime>
#include <iostream>

#include "FPSCounter.h"
#include "InputManager.h"
#include "LeaveMenuCommand.h"
#include "LevelLoader.h"
#include "NullSoundSystem.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "TextComponent.h"

using namespace dae;

void BubbleBobble::Create()
{
	// Seed rand() with current time
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	ServiceLocator::RegisterSoundSystem(new NullSoundSystem());

	//Make the main menu level
	MakeMainMenu();
	MakeAllLevels();


	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "WASD and spacebar are the current controls\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";

}

void BubbleBobble::MakeMainMenu()
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

void BubbleBobble::MakeAllLevels()
{
	auto& pSceneManager = SceneManager::GetInstance();
	Scene* level01 = pSceneManager.CreateScene("Level01");
	Scene* level02 = pSceneManager.CreateScene("Level02");
	Scene* level03 = pSceneManager.CreateScene("Level03");

	LevelLoader::LoadLevel(level01, 1, true);
	LevelLoader::LoadLevel(level02, 2, false);
	LevelLoader::LoadLevel(level03, 3, false);
}
