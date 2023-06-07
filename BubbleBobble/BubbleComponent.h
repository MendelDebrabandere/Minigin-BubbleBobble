#pragma once
#include <glm/vec2.hpp>

#include "Component.h"

class BubbleComponent : public dae::Component
{
public:
	enum class BubbleState
	{
		Shooting,
		Hovering,
		ReachedTop,
		Popping,
		EnemyDying
	};

	BubbleComponent() = default;
	virtual ~BubbleComponent() = default;

	BubbleComponent(const BubbleComponent& other) = delete;
	BubbleComponent(BubbleComponent&& other) = delete;
	BubbleComponent& operator=(const BubbleComponent& other) = delete;
	BubbleComponent& operator=(BubbleComponent&& other) = delete;

	void Initialize() override;
	void Update() override;
	void SetShootDirection(bool right);

	BubbleState GetState() const;
	bool HasEnemyInside() const;

private:
	BubbleState m_CurrentState{ BubbleState::Shooting };

	void PickUpEnemy(dae::GameObject* go);
	void Pop(bool byPlayer);

	float m_Timer{};
	bool m_DirectionRight{};

	//This is a bool and not a state
	//It still has to finish shooting, hovering and reach top
	//with an enemy inside
	bool m_HasEnemyInside{};
	bool m_ZenChan{true};

	glm::vec2 m_RandomGoToPos{};
};
