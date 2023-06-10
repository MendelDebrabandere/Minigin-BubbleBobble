#include "HUD.h"

#include "ResourceManager.h"
#include "AvatarComponent.h"
#include "HealthDisplay.h"
#include "ScoreDisplay.h"
#include "TextComponent.h"

using namespace dae;

GameObject* HUD::CreateHUD(Scene* pScene , AvatarComponent* avatarComp )
{
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };

	// ScoreDisplay
	const auto pName = pScene->CreateGameObject();
	pName->AddComponent<TextureComponent>();
	pName->AddComponent<TextComponent>()->SetFont(pFont);

	// ScoreDisplay
	const auto pScore = pScene->CreateGameObject();
	pScore->AddComponent<TextureComponent>();
	pScore->AddComponent<TextComponent>()->SetFont(pFont);
	pScore->AddComponent<ScoreDisplay>()->SetPlayer(avatarComp);

	// HealthDisplay
	const auto pHealth = pScene->CreateGameObject();
	pHealth->AddComponent<TextureComponent>();
	pHealth->AddComponent<TextComponent>()->SetFont(pFont);
	pHealth->AddComponent<HealthDisplay>()->SetPlayer(avatarComp);


	if (avatarComp->GetColor() == AvatarComponent::AvatarColor::green)
	{
		pName->GetComponent<TextComponent>()->SetText("Green player: ");
		pName->GetTransform()->SetWorldPosition(1045, 550);
		pHealth->GetTransform()->SetWorldPosition(1045, 610);
		pScore->GetTransform()->SetWorldPosition(1045, 670);
	}
	else
	{
		pName->GetComponent<TextComponent>()->SetText("Blue player: ");
		pName->GetTransform()->SetWorldPosition(1045, 150);
		pHealth->GetTransform()->SetWorldPosition(1045, 210);
		pScore->GetTransform()->SetWorldPosition(1045, 270);
	}

	return pScore;
}
