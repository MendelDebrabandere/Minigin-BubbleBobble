#include "HUD.h"

#include "ResourceManager.h"
#include "AvatarComponent.h"
#include "HealthDisplay.h"
#include "ScoreDisplay.h"
#include "TextComponent.h"

using namespace dae;

GameObject* HUD::CreateHUD(Scene* pScene)
{
	// ScoreDisplay
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };

	AvatarComponent* avatarComp{};
	for (auto& go : pScene->GetAllObjects())
	{
		avatarComp = go->GetComponent<AvatarComponent>();
		if (avatarComp)
			break;
	}

	const auto pScore = pScene->CreateGameObject();
	pScore->AddComponent<TextureComponent>();
	pScore->AddComponent<TextComponent>()->SetFont(pFont);
	pScore->AddComponent<ScoreDisplay>()->SetPlayer(avatarComp);
	pScore->GetTransform()->SetWorldPosition(1070, 750);

	const auto pHealth = pScene->CreateGameObject();
	pHealth->AddComponent<TextureComponent>();
	pHealth->AddComponent<TextComponent>()->SetFont(pFont);
	pHealth->AddComponent<HealthDisplay>()->SetPlayer(avatarComp);
	pHealth->GetTransform()->SetWorldPosition(1070, 650);

	return pScore;
}
