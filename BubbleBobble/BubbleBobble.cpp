#include "BubbleBobble.h"

#include <random>
#include <ctime>
#include "GameSceneCreator.h"
#include "SceneManager.h"

void BubbleBobble::Create(dae::Minigin* pEngine)
{
	// Seed rand() with current time
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	dae::Scene* pGameScene{ pEngine->GetSceneManager()->CreateScene("Game") };
	pEngine->GetSceneManager()->SetActiveScene(pGameScene);

	GameSceneCreator::CreateGameScene(pGameScene);
}
