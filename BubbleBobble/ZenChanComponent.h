#pragma once
#include "Component.h"

class ZenChanComponent : public dae::Component
{
public:
	ZenChanComponent() = default;
	virtual ~ZenChanComponent() = default;

	ZenChanComponent(const ZenChanComponent& other) = delete;
	ZenChanComponent(ZenChanComponent&& other) = delete;
	ZenChanComponent& operator=(const ZenChanComponent& other) = delete;
	ZenChanComponent& operator=(ZenChanComponent&& other) = delete;

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
