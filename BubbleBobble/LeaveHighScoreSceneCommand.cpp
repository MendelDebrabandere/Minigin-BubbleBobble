#include "LeaveHighScoreSceneCommand.h"

#include "HighScoreLoader.h"
#include "SceneManager.h"
#include "SceneSwapper.h"
#include "MainMenuScene.h"
#include "Scene.h"
#include "TypingKeyboardComponent.h"

void LeaveHighScoreSceneCommand::Execute()
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto scene = sceneManager.GetActiveScene();

	//get name that was input
	std::string name{};
	for (auto& go : scene->GetAllObjects())
	{
		const auto typer = go->GetComponent<TypingKeyboardComponent>();
		if (typer)
			name = typer->GetInput();
	}

	//save highscore
	HighScoreLoader::AddHighScore(name, m_Score);

	//Load main menu
	MainMenuScene::Create();

	SceneSwapper::GetInstance().m_State = SceneSwapper::GameState::Menu;
}
