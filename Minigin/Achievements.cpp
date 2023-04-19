#include "Achievements.h"

#include "GameObject.h"
#include "ScoreComponent.h"

using namespace dae;

AchievementObserver::AchievementObserver()
{
	m_SteamAchievements = new CSteamAchievements(m_Achievements.data(), 4);
}

AchievementObserver::~AchievementObserver()
{
	delete m_SteamAchievements;
}

void AchievementObserver::Notify(const GameObject* actor, Event event)
{
	switch (event)
	{
	case Event::ScoreUpdated:
		{
			//TODO: Every time that you have more than 500 points the achievemnt gets called
			if (actor->GetComponent<ScoreComponent>()->GetScore() >= 500)
				Unlock("ACH_WIN_ONE_GAME");
		break;
		}
	}
}

void AchievementObserver::Unlock(const char* ID) const
{
	m_SteamAchievements->SetAchievement(ID);
}
