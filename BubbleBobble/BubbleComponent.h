#pragma once
#include "Component.h"

class BubbleComponent : public dae::Component
{
public:
	BubbleComponent() = default;
	virtual ~BubbleComponent() = default;

	BubbleComponent(const BubbleComponent& other) = delete;
	BubbleComponent(BubbleComponent&& other) = delete;
	BubbleComponent& operator=(const BubbleComponent& other) = delete;
	BubbleComponent& operator=(BubbleComponent&& other) = delete;

	void Update() override;
	void SetShootDirection(bool right);

private:
	enum class BubbleState
	{
		Shooting,
		Hovering,
		EnemyInside
	};
	BubbleState m_CurrentState{ BubbleState::Shooting };

	void DoMovementLogic();
	void DoCollisionLogic();
	void PickUpEnemy(dae::GameObject* go);
	void PopByPlayer(dae::GameObject* go);

	float m_Timer{};
	bool m_DirectionRight{};

	bool m_HasReachedTheTop{};
};
