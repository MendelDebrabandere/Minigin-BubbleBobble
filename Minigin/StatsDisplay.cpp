#include "StatsDisplay.h"

#include <string>
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
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
			if (m_pHealthTextObject)
			{
				const auto healthComp = m_pPlayerObj->GetComponent<HealthComponent>();

				const auto pTextComponent = m_pHealthTextObject->GetComponent<TextComponent>();

				if (pTextComponent && healthComp)
					pTextComponent->SetText("Health: " + std::to_string(healthComp->GetHealth()));
			}
		break;
		}
		case Event::ScoreUpdated:
		{
			if (m_pScoreTextObject)
			{
				const auto scoreComp = m_pPlayerObj->GetComponent<ScoreComponent>();

				const auto pTextComponent = m_pScoreTextObject->GetComponent<TextComponent>();

				if (pTextComponent && scoreComp)
				{
					pTextComponent->SetText("Points: " + std::to_string(scoreComp->GetScore()));
				}
			}
		break;
		}
		case Event::ActorDied:
		{
			//Destroy the gameobject that uses text component for this observer
			m_pHealthTextObject->Destroy();
			m_pScoreTextObject->Destroy();
			//Destroy this observer since the player it is tracking no longer exists
			this->Destroy();
		break;
		}
		}
	}
}

void StatsDisplay::SetPlayerObject(GameObject* actor)
{
	m_pPlayerObj = actor;
	//Update text objects by notifying
	Notify(m_pPlayerObj, Event::HealthUpdated);
	Notify(m_pPlayerObj, Event::ScoreUpdated);
}

void StatsDisplay::SetHealthTextObject(GameObject* actor)
{
	m_pHealthTextObject = actor;
	//Update text object by notifying
	Notify(m_pPlayerObj, Event::HealthUpdated);
}

void StatsDisplay::SetScoreTextObject(GameObject* actor)
{
	m_pScoreTextObject = actor;
	//Update text object by notifying
	Notify(m_pPlayerObj, Event::ScoreUpdated);
}