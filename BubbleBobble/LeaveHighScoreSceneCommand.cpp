#include "LeaveHighScoreSceneCommand.h"

#include "SceneManager.h"
#include "SceneSwapper.h"
#include "MainMenuScene.h"

void LeaveHighScoreSceneCommand::Execute()
{
	//auto& sceneManager = dae::SceneManager::GetInstance();
	//auto scene = sceneManager.GetActiveScene();

	//save highscore





	//Load main menu
	MainMenuScene::Create();

	SceneSwapper::GetInstance().m_State = SceneSwapper::GameState::Menu;
}
