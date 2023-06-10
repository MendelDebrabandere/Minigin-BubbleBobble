#include "HUD.h"

#include "ResourceManager.h"
#include "AvatarComponent.h"
#include "HealthDisplay.h"
#include "PlayerMaitaComponent.h"
#include "ScoreDisplay.h"
#include "TextComponent.h"

using namespace dae;

GameObject* HUD::CreateHUD(Scene* pScene , AvatarComponent* avatarComp, PlayerMaitaComponent* maitaComp )
{
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Retro.otf", 30) };

	// ScoreDisplay
	const auto pScore = pScene->CreateGameObject();
	pScore->AddComponent<TextureComponent>();
	pScore->AddComponent<TextComponent>()->SetFont(pFont);
	pScore->AddComponent<ScoreDisplay>()->SetPlayer(avatarComp);

	// HealthDisplay
	const auto pHealth = pScene->CreateGameObject();
	pHealth->AddComponent<TextureComponent>();
	pHealth->AddComponent<TextComponent>()->SetFont(pFont);
	pHealth->AddComponent<HealthDisplay>()->SetSubject(&avatarComp->m_HealthChange);


	if (avatarComp->GetColor() == AvatarComponent::AvatarColor::green)
	{
		pHealth->GetTransform()->SetWorldPosition(1045, 610);
		pScore->GetTransform()->SetWorldPosition(1045, 670);
		pHealth->GetComponent<TextComponent>()->SetColor(50, 255, 50);
		pScore->GetComponent<TextComponent>()->SetColor(50, 255, 50);
	}
	else
	{
		pHealth->GetTransform()->SetWorldPosition(1045, 210);
		pScore->GetTransform()->SetWorldPosition(1045, 270);
		pHealth->GetComponent<TextComponent>()->SetColor(50, 50, 255);
		pScore->GetComponent<TextComponent>()->SetColor(50, 50, 255);
	}

	//Maita UI
	if (maitaComp)
	{
		pScore->Destroy();

		// HealthDisplay
		const auto pMaitaHealth = pScene->CreateGameObject();
		pMaitaHealth->AddComponent<TextureComponent>();
		pMaitaHealth->AddComponent<TextComponent>()->SetFont(pFont);
		pMaitaHealth->AddComponent<HealthDisplay>()->SetSubject(&maitaComp->m_HealthChange);
		pMaitaHealth->GetTransform()->SetWorldPosition(1045, 210);
	}

	return pScore;
}
