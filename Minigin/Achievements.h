#pragma once
#include <cstddef>
#include <vector>

#include "CSteamAchievements.h"
#include "Observer.h"

namespace dae
{
	enum class Achievement
	{
		FirstBlood
	};

	class AchievementObserver final : public Observer
	{
	public:
		AchievementObserver();
		virtual ~AchievementObserver();
		AchievementObserver(const AchievementObserver& other) = delete;
		AchievementObserver(AchievementObserver&& other) = delete;
		AchievementObserver& operator=(const AchievementObserver& other) = delete;
		AchievementObserver& operator=(AchievementObserver&& other) = delete;

		void Notify(const GameObject* actor, Event event) override;

	private:
		// Defining our achievements
		enum EAchievements
		{
			ACH_WIN_ONE_GAME = 0,
			ACH_WIN_100_GAMES = 1,
			ACH_TRAVEL_FAR_ACCUM = 2,
			ACH_TRAVEL_FAR_SINGLE = 3,
		};

		// Achievement array which will hold data about the achievements and their state
		std::vector<Achievement_t> m_Achievements =
		{
			_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
			_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
			_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
			_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
		};

		CSteamAchievements* m_SteamAchievements = NULL;

		void Unlock(const char* ID) const;
	};
}

