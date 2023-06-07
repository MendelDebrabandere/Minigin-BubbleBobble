#pragma once
#include "Component.h"

class EnemyComponent : public dae::Component
{
public:
	EnemyComponent() = default;
	virtual ~EnemyComponent() = default;

	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;

	void Update() override;

	void MultiplyMoveSpeed(float value);
	void ResetMoveSpeed();

private:
	enum class BehaviorState
	{
		Wander,
		Jumping
	};

	BehaviorState m_CurrBehavior{ BehaviorState::Wander };

	bool m_WalkingRight{ false };
	float m_WalkingSpeed{ 150.f };

	float m_JumpingCooldown{ 2 };
	float m_JumpSpeed{ -450 };


	float m_ChangeWalkDirTimer{ float(rand() % 5 + 5) };
};
