#include "RockComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "Timer.h"


void RockComponent::Initialize()
{
	m_HorMoveSpeed = 300.f;
	m_CurrState = RockState::Rolling;
}

void RockComponent::Update()
{
	float elapsedSec = dae::Time::GetInstance().GetDelta();
	auto physComp = m_pOwner->GetComponent<dae::PhysicsComponent>();
	auto collisionData = physComp->GetCollisionState();

	switch (m_CurrState)
	{
	case RockState::Rolling:
	{

		//break if it hits wall
		if (collisionData.LeftCollision || collisionData.RightCollision)
		{
			Crash();
			break;
		}

		//set horizontal movespeed
		int moveDir = m_MoveRight ? 1 : -1;
		m_pOwner->GetTransform()->Translate(moveDir * m_HorMoveSpeed * elapsedSec, 0);
		break;
	}
	case RockState::Crashing:
	{
		m_CrashingTimer += elapsedSec;
		if (m_CrashingTimer > 0.59f)
		{
			m_pOwner->Destroy();
		}
		break;
	}
	}

}

void RockComponent::SetMoveRight(bool right)
{
	m_MoveRight = right;
}

void RockComponent::Crash()
{
	m_CurrState = RockState::Crashing;
	auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	spriteComp->SetAnimVariables(2, 4, 0.2f, 4, 7);
	spriteComp->Scale(4);
}

bool RockComponent::CanDamage() const
{
	return m_CurrState == RockState::Rolling;
}
