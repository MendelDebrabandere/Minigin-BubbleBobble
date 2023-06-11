#pragma once
#include "Component.h"

class RockComponent final : public dae::Component
{
public:
	RockComponent() = default;
	~RockComponent() override = default;

	RockComponent(const RockComponent& other) = delete;
	RockComponent(RockComponent&& other) = delete;
	RockComponent& operator=(const RockComponent& other) = delete;
	RockComponent& operator=(RockComponent&& other) = delete;

	void Initialize() override;
	void Update() override;

	void SetMoveRight(bool right);
	void Crash();

	bool CanDamage() const;

private:
	enum class RockState
	{
		Rolling,
		Crashing
	};

	RockState m_CurrState{};

	float m_HorMoveSpeed{};
	bool m_MoveRight{};

	float m_CrashingTimer{};
};
