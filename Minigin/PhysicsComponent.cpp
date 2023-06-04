#include "PhysicsComponent.h"

#include "ColliderComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Timer.h"

using namespace dae;

void PhysicsComponent::FixedUpdate()
{
	m_IsGrounded = false;
	DoGravityLogic();
}

void PhysicsComponent::SetPhysicsSettings(bool gravity, bool collision, bool isStatic)
{
	m_Gravity = gravity;
	m_Collision = collision;
	m_Static = isStatic;
}

void PhysicsComponent::Jump(float speed)
{
	m_VerticalSpeed = speed;
}

bool PhysicsComponent::HasCollision() const
{
	return m_Collision;
}

//Collision is going to happen if one of the objects has m_Collision to true,
//They will only overlap if both have m_Collision to false
//This function also only gets called when they are already overlapping
void PhysicsComponent::DoCollisionLogic(PhysicsComponent* other, std::pair<ColliderComponent::OverlapData, float> overlapData)
{
	// dont do calculations if it is static or collision is off
	if (m_Static == true)
		return;

	
	auto myCollider = m_pOwner->GetComponent<ColliderComponent>();

	//Platforms only collide from top
	if (other->m_Platform && overlapData.first != ColliderComponent::OverlapData::Bottom)
		return;

	switch (overlapData.first)
	{
	case ColliderComponent::OverlapData::Top:
	{
		m_pOwner->GetTransform()->Translate(0, overlapData.second);
		myCollider->UpdatePos();
		m_VerticalSpeed = 0.f;
		break;
	}
	case ColliderComponent::OverlapData::Bottom:
	{
		if (m_VerticalSpeed > -1.f)
		{
			m_pOwner->GetTransform()->Translate(0, -overlapData.second);
			myCollider->UpdatePos();
			m_IsGrounded = true;
			m_VerticalSpeed = 0.f;
		}
		break;
	}
	case ColliderComponent::OverlapData::Left:
	{
		m_pOwner->GetTransform()->Translate(overlapData.second, 0);
		myCollider->UpdatePos();
		break;
	}
	case ColliderComponent::OverlapData::Right:
	{
		m_pOwner->GetTransform()->Translate(-overlapData.second, 0);
		myCollider->UpdatePos();
		break;
	}
	case ColliderComponent::OverlapData::Not:
		break;
	}
}

void PhysicsComponent::DoGravityLogic()
{
	if (m_Gravity == false || m_Static == true)
		return;

	const float fixedTimeStep{ Time::GetInstance().GetFixedTimeStep() };

	m_VerticalSpeed += m_GravityAccel * fixedTimeStep;
	m_VerticalSpeed = std::min(m_MaxFallSpeed, m_VerticalSpeed);

	//If the player or anything with a collider reaches outside of the screen in Y direction
	//TP back to the top
	auto myCollider = m_pOwner->GetComponent<ColliderComponent>();
	if (myCollider)
	{
		glm::vec2 worldPos = m_pOwner->GetTransform()->GetWorldPosition();
		if (worldPos.y >= 800)
		{
			m_pOwner->GetTransform()->SetWorldPosition(worldPos.x, 0 - myCollider->GetSize().y);
		}
	}



	m_pOwner->GetTransform()->Translate(0, fixedTimeStep * m_VerticalSpeed);
}
