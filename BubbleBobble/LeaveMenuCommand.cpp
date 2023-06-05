#include "LeaveMenuCommand.h"

#include "BubbleBobble.h"
#include "BubbleComponent.h"
#include "EnemyComponent.h"
#include "FoodComponent.h"
#include "InputManager.h"
#include "LevelLoader.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

void LeaveMenuCommand::Execute()
{
	//Remove the previous scene (main menu)
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto* pGameScene = sceneManager.GetActiveScene();
	pGameScene->RemoveAll();
	dae::InputManager::GetInstance().RemoveAllInputs();

	//load the first level
	pGameScene->SetName("1"); // level 1
	LevelLoader::LoadLevel(pGameScene, 1); // level 1
	sceneManager.SetActiveScene(pGameScene);

	//Set a scene selector function so it can change level automatically in game
	dae::SceneManager::GetInstance().SetSceneSelector([]()
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
				auto& sceneManager = dae::SceneManager::GetInstance();
				auto* pGameScene = sceneManager.GetActiveScene();
				auto name = pGameScene->GetName();

				pGameScene->RemoveAll();
				dae::InputManager::GetInstance().RemoveAllInputs();

				if (std::isdigit(name[0]))
				{
					int levelNr = std::stoi(name);

					if (levelNr < 3)
					{
						pGameScene->SetName(std::to_string(levelNr + 1));
						LevelLoader::LoadLevel(pGameScene, levelNr + 1);
						sceneManager.SetActiveScene(pGameScene);
					}
					else
					{
						BubbleBobble::MakeMainMenu();
					}
				}
			}
		});

	//Start playing the in game music
	dae::ServiceLocator::GetSoundSystem().PlayMusic("../Data/Sound/MainTheme.mp3", 15, -1);
}
