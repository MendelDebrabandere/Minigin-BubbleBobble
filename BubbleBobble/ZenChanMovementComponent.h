#pragma once
#include "Component.h"

class ZenChanMovementComponent : public dae::Component
{
public:
	ZenChanMovementComponent() = default;
	virtual ~ZenChanMovementComponent() = default;

	ZenChanMovementComponent(const ZenChanMovementComponent& other) = delete;
	ZenChanMovementComponent(ZenChanMovementComponent&& other) = delete;
	ZenChanMovementComponent& operator=(const ZenChanMovementComponent& other) = delete;
	ZenChanMovementComponent& operator=(ZenChanMovementComponent&& other) = delete;

	void Update() override;

private:
	enum class BehaviorState
	{
		Wander,
		Jumping
	};

	BehaviorState m_CurrBehavior{ BehaviorState::Wander };

	bool m_WalkingRight{ false };
	float m_WalkingSpeed{ 150.f };

	float m_JumpingCooldown{2};
	float m_JumpSpeed{ -450 };

	bool m_Charging{};
	float m_ChargingTimer{ float(rand() % 20 + 10) };

	float m_ChangeWalkDirTimer{ float(rand() % 5 + 5) };
};
