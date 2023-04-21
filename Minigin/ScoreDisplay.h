#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	enum class LootType;
	class Hero;

	class ScoreDisplay final : public Component, public Observer<LootType>
	{
	public:
		ScoreDisplay() = default;
		ScoreDisplay(Hero* hero);
		virtual ~ScoreDisplay();

		ScoreDisplay(const ScoreDisplay& other) = delete;
		ScoreDisplay(ScoreDisplay&& other) = delete;
		ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
		ScoreDisplay& operator=(ScoreDisplay&& other) = delete;

	private:
		void HandleEvent(LootType type) override;
		void OnSubjectDestroy() override {}
		void UpdateScoreText() {}

		int m_score{};
		Hero* m_pHero{};

	};
}

