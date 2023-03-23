#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSCounter.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"

using namespace dae;

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	const auto pBackgroundTexture{ ResourceManager::GetInstance().LoadTexture("background.tga") };
	const auto pLogoTexture{ ResourceManager::GetInstance().LoadTexture("logo.tga") };

	// BACKGROUND
	auto go = std::make_shared<GameObject>();
	go->Init();
	go->AddComponent<TextureComponent>()->SetTexture(pBackgroundTexture);
	scene.Add(go);

	// DAE LOGO
	go = std::make_shared<GameObject>();
	go->Init();
	go->GetComponent<Transform>()->SetWorldPosition(216, 180);
	go->AddComponent<TextureComponent>()->SetTexture(pLogoTexture);
	go->AddComponent<FPSCounter>();
	scene.Add(go);

	// TEXT
	go = std::make_shared<GameObject>();
	go->Init();
	go->GetComponent<Transform>()->SetWorldPosition(80, 20);
	go->AddComponent<TextureComponent>();
	const auto pHeaderText{ go->AddComponent<TextComponent>() };
	pHeaderText->SetFont(pFont);
	pHeaderText->SetText("Programming 4 Assignment");
	scene.Add(go);

	// FPS COUNTER
	go = std::make_shared<GameObject>();
	go->Init();
	go->GetComponent<Transform>()->SetWorldPosition(0.0f, 0.0f);
	go->AddComponent<TextureComponent>();
	go->AddComponent<FPSCounter>();
	const auto pText{ go->AddComponent<TextComponent>() };
	pText->SetFont(pFont);
	scene.Add(go);

	// Create the main character gameobject and assign a controller to it
	const auto pCharacter = std::make_shared<GameObject>();
	pCharacter->Init();
	pCharacter->GetComponent<Transform>()->SetWorldPosition(350, 300);
	pCharacter->AddComponent<TextureComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("MainCharacter.png"));
	InputManager::GetInstance().AddControllerCommands<MoveCommand>(pCharacter.get(), XBox360Controller::ControllerButton::LeftThumbStick, 0);
	scene.Add(pCharacter);

	// Create a GO that renders the enemy and rotates around the character at double speed
	const auto pEnemy = std::make_shared<GameObject>();
	pEnemy->Init();
	pEnemy->GetComponent<Transform>()->SetWorldPosition(250, 300);
	pEnemy->AddComponent<TextureComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy.png"));
	InputManager::GetInstance().AddControllerCommands<MoveCommand>(pEnemy.get(), XBox360Controller::ControllerButton::LeftThumbStick, 1);
	scene.Add(pEnemy);
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}