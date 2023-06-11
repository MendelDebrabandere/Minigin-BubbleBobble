#pragma once
#include "Component.h"

class EnemyComponent final : public dae::Component
{
public:
	EnemyComponent() = default;
	~EnemyComponent() override = default;

	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;

	void Initialize() override;
	void Update() override;

	void MultiplyMoveSpeed(float value);
	void ResetMoveSpeed();

	bool GetMoveRight() const;

private:
	enum class BehaviorState
	{
		Wander,
		Jumping
	};

	BehaviorState m_CurrBehavior{ BehaviorState::Wander };

	bool m_WalkingRight{};
	float m_WalkingSpeed{};

	float m_JumpingCooldown{};
	float m_JumpSpeed{};

	float m_ChangeWalkDirTimer{};

	dae::Transform* m_pAvatarTransform{};
};
