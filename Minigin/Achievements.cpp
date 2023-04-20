#include "Achievements.h"

#include "Events.h"
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

void AchievementObserver::Notify(const GameObject* actor, int eventID)
{
	switch (Event(eventID))
	{
	case Event::ScoreUpdated:
		{
			if (actor->GetComponent<ScoreComponent>()->GetScore() >= 500)
				Unlock("ACH_WIN_ONE_GAME");
		break;
		}
	}
}

void AchievementObserver::Unlock(const char* ID)
{
	//Check if the achievement has already been collected
	for (const std::string& achievement : m_CollectedAchievements)
	{
		if (achievement.c_str() == ID)
			return;
	}

	m_SteamAchievements->SetAchievement(ID);
	m_CollectedAchievements.push_back(std::string(ID));
}
