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

	// Name
	const auto pName = pScene->CreateGameObject();
	pName->AddComponent<TextureComponent>();
	pName->AddComponent<TextComponent>()->SetFont(pFont);
	pName->AddComponent<ScoreDisplay>()->Disable();

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
		pName->GetComponent<TextComponent>()->SetText("Green: ");
		pName->GetTransform()->SetWorldPosition(1045, 550);
		pHealth->GetTransform()->SetWorldPosition(1045, 610);
		pScore->GetTransform()->SetWorldPosition(1045, 670);
		pName->GetComponent<TextComponent>()->SetColor(50, 255, 50);
		pHealth->GetComponent<TextComponent>()->SetColor(50, 255, 50);
		pScore->GetComponent<TextComponent>()->SetColor(50, 255, 50);
	}
	else
	{
		pName->GetComponent<TextComponent>()->SetText("Blue: ");
		pName->GetTransform()->SetWorldPosition(1045, 150);
		pHealth->GetTransform()->SetWorldPosition(1045, 210);
		pScore->GetTransform()->SetWorldPosition(1045, 270);
		pName->GetComponent<TextComponent>()->SetColor(50, 50, 255);
		pHealth->GetComponent<TextComponent>()->SetColor(50, 50, 255);
		pScore->GetComponent<TextComponent>()->SetColor(50, 50, 255);
	}

	//Maita UI
	if (maitaComp)
	{
		pScore->Destroy();

		// Name
		const auto pMaitaName = pScene->CreateGameObject();
		pMaitaName->AddComponent<TextureComponent>();
		pMaitaName->AddComponent<TextComponent>()->SetFont(pFont);
		pMaitaName->AddComponent<ScoreDisplay>()->Disable();
		pMaitaName->GetComponent<TextComponent>()->SetText("Maita: ");
		pMaitaName->GetTransform()->SetWorldPosition(1045, 150);

		// HealthDisplay
		const auto pMaitaHealth = pScene->CreateGameObject();
		pMaitaHealth->AddComponent<TextureComponent>();
		pMaitaHealth->AddComponent<TextComponent>()->SetFont(pFont);
		pMaitaHealth->AddComponent<HealthDisplay>()->SetSubject(&maitaComp->m_HealthChange);
		pMaitaHealth->GetTransform()->SetWorldPosition(1045, 210);
	}

	return pScore;
}
