#include "Achievements.h"

using namespace dae;

AchievementObserver::AchievementObserver()
{
	m_SteamAchievements = new CSteamAchievements(m_Achievements.data(), 4);
}

AchievementObserver::~AchievementObserver()
{
	if (m_SteamAchievements)
		delete m_SteamAchievements;
}

void AchievementObserver::Notify(const GameObject* /*actor*/, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
		Unlock("ACH_WIN_ONE_GAME");
		break;
	}
}

void AchievementObserver::Unlock(const char* ID)
{
	m_SteamAchievements->SetAchievement(ID);
}
