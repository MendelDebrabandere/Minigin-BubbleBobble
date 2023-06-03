#pragma once
#include <glm/vec2.hpp>

#include "Component.h"

class BubbleFlyingComponent : public dae::Component
{
public:
	BubbleFlyingComponent() = default;
	virtual ~BubbleFlyingComponent() = default;

	BubbleFlyingComponent(const BubbleFlyingComponent& other) = delete;
	BubbleFlyingComponent(BubbleFlyingComponent&& other) = delete;
	BubbleFlyingComponent& operator=(const BubbleFlyingComponent& other) = delete;
	BubbleFlyingComponent& operator=(BubbleFlyingComponent&& other) = delete;

	void Update() override;
	void SetShootDirection(bool right);

private:
	float m_Timer{};
	bool m_DirectionRight{};

	bool m_HasReachedTheTop{};
};
