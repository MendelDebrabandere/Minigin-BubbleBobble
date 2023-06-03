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
	float m_Timer{};
	bool m_DirectionRight{};

	bool m_HasReachedTheTop{};
};
