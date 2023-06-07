#include "HUD.h"

#include "ResourceManager.h"
#include "AvatarComponent.h"
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

	return pScore;
}
