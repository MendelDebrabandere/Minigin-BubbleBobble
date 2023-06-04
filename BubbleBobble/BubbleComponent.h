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

	void Initialize() override;
	void Update() override;
	void SetShootDirection(bool right);

private:
	enum class BubbleState
	{
		Shooting,
		Hovering,
		ReachedTop,
	};
	BubbleState m_CurrentState{ BubbleState::Shooting };

	void DoMovementLogic();
	void PickUpEnemy(dae::GameObject* go);
	void PopByPlayer(dae::GameObject* go);

	float m_Timer{};
	bool m_DirectionRight{};

	//This is a bool and not a state
	//It still has to finish shooting, hovering and reach top
	//with an enemy inside
	bool m_HasEnemyInside{};
};
