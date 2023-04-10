#include "StatsDisplay.h"

#include <string>
#include "GameObject.h"
#include "HealthComponent.h"
#include "Subject.h"
#include "TextComponent.h"

using namespace dae;

void StatsDisplay::Notify(const GameObject* actor, Event event)
{
	//Only update stats if the actor is the player
	if (actor == m_pPlayerObj)
	{
		switch (event)
		{
		case Event::HealthUpdated:
		{
			if (m_pPlayerObj && m_pTextObject)
			{
				const int health = m_pPlayerObj->GetComponent<HealthComponent>()->GetHealth();

				const auto pTextComponent = m_pTextObject->GetComponent<TextComponent>();

				if (pTextComponent && health)
					pTextComponent->SetText("Health: " + std::to_string(health));

			}
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
		case Event::ActorDied:
		{
			//Destroy the gameobject that uses text component for this observer
			m_pTextObject->Destroy();
			this->Destroy();
		break;
		}
		}
	}
}

void StatsDisplay::SetPlayerObject(GameObject* actor)
{
	m_pPlayerObj = actor;
	Notify(m_pPlayerObj, Event::HealthUpdated);
}

void dae::StatsDisplay::SetTextObject(GameObject* actor)
{
	m_pTextObject = actor;
	Notify(m_pPlayerObj, Event::HealthUpdated);
}
