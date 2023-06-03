#include "PhysicsComponent.h"

#include "ColliderComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Timer.h"

using namespace dae;

void PhysicsComponent::FixedUpdate()
{
	m_IsGrounded = false;
	DoCollisionLogic();
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

void PhysicsComponent::DoCollisionLogic()
{
	// dont do calculations if it is static or collision is off
	if (m_Collision == false || m_Static == true)
		return;

	//only continue of you have a collider
	auto myCollider = m_pOwner->GetComponent<ColliderComponent>();
	if (myCollider == nullptr)
		return;

	Scene* scene = SceneManager::GetInstance().GetActiveScene();

	//For all objects
	for (auto& object : scene->GetAllObjects())
	{
		if (object.get() == m_pOwner)
			continue;

		//if they have physics and colliders
		auto otherPhysicsComp = object->GetComponent<PhysicsComponent>();
		auto otherColliderComp = object->GetComponent<ColliderComponent>();
		if (otherPhysicsComp && otherColliderComp)
		{
			//only go on if they have collision on
			if (otherPhysicsComp->m_Collision == false)
				continue;

			//if you are overlapping
			const auto overlapData = myCollider->IsOverlappingWith(otherColliderComp);

			//Platforms only collide from top
			if (otherPhysicsComp->m_Platform && overlapData.first != ColliderComponent::OverlapData::Bottom)
				continue;

			switch (overlapData.first)
			{
			case ColliderComponent::OverlapData::Top:
			{
				m_pOwner->GetTransform()->Translate(0, overlapData.second);
				myCollider->FixedUpdate();
				m_VerticalSpeed = 0.f;
				break;
			}
			case ColliderComponent::OverlapData::Bottom:
			{
				if (m_VerticalSpeed > -1.f)
				{
					m_pOwner->GetTransform()->Translate(0, -overlapData.second);
					myCollider->FixedUpdate();
					m_IsGrounded = true;
					m_VerticalSpeed = 0.f;
				}
				break;
			}
			case ColliderComponent::OverlapData::Left:
			{
				m_pOwner->GetTransform()->Translate(overlapData.second, 0);
				myCollider->FixedUpdate();
				break;
			}
			case ColliderComponent::OverlapData::Right:
			{
				m_pOwner->GetTransform()->Translate(-overlapData.second, 0);
				myCollider->FixedUpdate();
				break;
			}
			case ColliderComponent::OverlapData::Not:
				break;
			}
		}
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
