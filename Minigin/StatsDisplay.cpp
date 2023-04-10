#include "StatsDisplay.h"

#include <string>
#include "GameObject.h"
#include "HealthComponent.h"
#include "TextComponent.h"

using namespace dae;

void StatsDisplay::Notify(const GameObject* actor, Event event)
{
	switch (event)
	{
	case Event::HealthUpdated:
	{
		const int lives = actor->GetComponent<HealthComponent>()->GetHealth();

		const auto pTextComponent = actor->GetComponent<TextComponent>();

		if (pTextComponent)
			pTextComponent->SetText("Health: " + std::to_string(lives));

		break;
	}
	case Event::ScoreUpdated:
	{
		////This is for testing purposes
		////TODO: finished version calls AttackComponent or something, this is still tbd.
		//m_AmountOfPoints += 50;

		////const auto& achievements = Achievements::GetInstance();

		////if (m_AmountOfPoints >= 500 && achievements.steamAchievements)
		////	achievements.steamAchievements->SetAchievement("ACH_WIN_ONE_GAME");

		//const auto pTextComponent = actor->GetComponent<TextComponent>();

		//if (pTextComponent == nullptr)
		//	return;

		//const std::string keyword = "Points";

		//if (pTextComponent->GetText().find(keyword) == std::string::npos)
		//	return;


		//pTextComponent->SetText("Points: " + std::to_string(m_AmountOfPoints));
		break;
	}
	}
}
