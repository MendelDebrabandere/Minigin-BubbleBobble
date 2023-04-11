#pragma once
#include "Component.h"

namespace dae
{
	class ScoreComponent final : public Component
	{
	public:
		ScoreComponent() = default;
		virtual ~ScoreComponent() = default;

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void SetScore(int amount);
		void AddScore(int amount);
		int GetScore() const;

	private:
		int m_Score{};
	};
}

