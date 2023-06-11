#include "SceneSwapper.h"

#include "AvatarComponent.h"
#include "BubbleComponent.h"
#include "EnemyComponent.h"
#include "EventQueue.h"
#include "FoodComponent.h"
#include "HealthDisplay.h"
#include "HighScoreScene.h"
#include "LevelLoader.h"
#include "MainMenuScene.h"
#include "SceneManager.h"
#include "ScoreDisplay.h"


using namespace dae;



void SceneSwapper::Init()
{
	SceneManager::GetInstance().SetSceneSwapperFunc([this]() {Update(); });
	MainMenuScene::Create();

	EventQueue::GetInstance().AddListener(this);
}

void SceneSwapper::Update()
{
	switch (m_State)
	{
	case GameState::Menu:
	{
		break;
	}
	case GameState::SinglePlayer:
	case GameState::Coop:
	{
		bool canChangeLevel{ true };
		//Check if it should change the scene to next level
		for (auto& object : dae::SceneManager::GetInstance().GetActiveScene()->GetAllObjects())
		{
			//dont change when there are still enemies
			if (object->HasComponent<EnemyComponent>())
			{
				canChangeLevel = false;
				break;
			}

			//dont change when there are still foods
			if (object->HasComponent<FoodComponent>())
			{
				canChangeLevel = false;
				break;
			}

			//dont change when there are still bubbles with enemies in them
			if (object->HasComponent<BubbleComponent>())
			{
				auto bubbleComponent = object->GetComponent<BubbleComponent>();
				if (bubbleComponent->GetState() == BubbleComponent::BubbleState::EnemyDying ||
					bubbleComponent->HasEnemyInside())
				{
					canChangeLevel = false;
					break;
				}
			}
		}

		//you can change the game mode now
		if (canChangeLevel)
		{
			SkipLevel();
		}
		break;
	}
	case GameState::Versus:
	{
		break;
	}
	case GameState::SetHighScore:
	{
		break;
	}
	}
}

void SceneSwapper::SkipLevel()
{
	if (m_State == GameState::SinglePlayer ||
		m_State == GameState::Coop || 
		m_State == GameState::Versus)
	{
		auto& sceneManager = SceneManager::GetInstance();
		auto* pGameScene = sceneManager.GetActiveScene();
		auto name = pGameScene->GetName();

		//Remove everything that doesnt have the avatar component
		auto& objVec = pGameScene->GetAllObjects();
		objVec.erase(std::remove_if(objVec.begin(), objVec.end(), [](std::unique_ptr<dae::GameObject>& go) {
			return (go->GetComponent<AvatarComponent>() == nullptr &&
				go->GetComponent<ScoreDisplay>() == nullptr &&
				go->GetComponent<HealthDisplay>() == nullptr);
			}), objVec.end());

		//keep inputs since the avatar doesnt get deleted
		//dae::InputManager::GetInstance().RemoveAllInputs();

		if (std::isdigit(name[0]))
		{
			int levelNr = std::stoi(name);

			if (levelNr < 3)
			{
				pGameScene->SetName(std::to_string(levelNr + 1));
				LevelLoader::LoadLevel(pGameScene, levelNr + 1, false);
				sceneManager.SetActiveScene(pGameScene);
			}
			else
			{
				if (m_State == GameState::SinglePlayer || m_State == GameState::Coop)
				{
					HighScoreScene::Create();
					m_State = GameState::SetHighScore;
				}
				else
				{
					MainMenuScene::Create();
					m_State = GameState::Menu;
				}
			}
		}
	}
}

void SceneSwapper::OnEvent(const dae::Event& e)
{
	if (e.name == "PlayerDied")
	{
		if (m_State == GameState::SinglePlayer || m_State == GameState::Coop)
		{
			HighScoreScene::Create();
			m_State = GameState::SetHighScore;
		}
		else
		{
			MainMenuScene::Create();
			m_State = GameState::Menu;
		}

	}
}

