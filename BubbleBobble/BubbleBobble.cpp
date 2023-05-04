#include "BubbleBobble.h"
#include "GameSceneCreator.h"
#include "SceneManager.h"

void BubbleBobble::Create(dae::Minigin* pEngine)
{
	dae::Scene* pGameScene{ pEngine->GetSceneManager()->CreateScene("Game") };
	pEngine->GetSceneManager()->SetActiveScene(pGameScene);

	GameSceneCreator::CreateGameScene(pGameScene);
}
