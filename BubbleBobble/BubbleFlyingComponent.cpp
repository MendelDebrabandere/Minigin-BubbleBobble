#include "BubbleFlyingComponent.h"
#include <SDL_stdinc.h>
#include "Timer.h"
#include "Transform.h"
#include "GameObject.h"

void BubbleFlyingComponent::Update()
{
	//increment timer
	float deltaTime = dae::Time::GetInstance().GetDelta();
	m_Timer += deltaTime;

	//Destroy if it reached the top
	if (m_HasReachedTheTop)
	{
		if (m_Timer >= 3.f)
			m_pOwner->Destroy();
		return;
	}

	//Get transform and position
	dae::Transform* pTransform{m_pOwner->GetTransform()};
	if (!pTransform) return;

	const glm::vec2 currPos = pTransform->GetWorldPosition();

	//Move object
	glm::vec2 posDelta{};
	if (m_Timer <= 0.5f)
	{
		constexpr float horMoveSpeed{ 450 };
		posDelta.x = (m_DirectionRight ? horMoveSpeed * deltaTime : -horMoveSpeed * deltaTime);
	}
	else
	{
		constexpr float vertMoveSpeed{ 100 };
		posDelta.y = -vertMoveSpeed * deltaTime;
	}

	//Check if it goes out of bounds
	if (currPos.x <= 70 || currPos.x >= 890)
	{
		posDelta.x = 0;
		m_Timer = 1.f;
	}
	if (currPos.y <= 70)
	{
		posDelta.y = 0;
		m_HasReachedTheTop = true;
		m_Timer = 0.f;
	}

	//Set transform
	pTransform->SetWorldPosition(currPos + posDelta);
}

void BubbleFlyingComponent::SetShootDirection(bool right)
{
	m_DirectionRight = right;
}
