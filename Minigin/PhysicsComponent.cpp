#include "PhysicsComponent.h"

#include "ColliderComponent.h"
#include "Scene.h"
#include "SceneManager.h"

using namespace dae;

void PhysicsComponent::Update()
{
	DoCollisionLogic();
	DoGravityLogic();
}

void PhysicsComponent::SetPhysicsSettings(bool gravity, bool collision, bool isStatic)
{
	m_Gravity = gravity;
	m_Collision = collision;
	m_Static = isStatic;
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
			if (otherPhysicsComp->GetCollision() == false)
				continue;

			//if you are overlapping
			const auto overlapData = myCollider->IsOverlappingWith(otherColliderComp);
			switch (overlapData.first)
			{
			case ColliderComponent::OverlapData::Top:
			{
				m_pOwner->GetTransform()->Translate(0, overlapData.second);
				myCollider->Update();
				break;
			}
			case ColliderComponent::OverlapData::Bottom:
			{
				m_pOwner->GetTransform()->Translate(0, -overlapData.second);
				myCollider->Update();
				m_IsGrounded = true;
				break;
			}
			case ColliderComponent::OverlapData::Left:
			{
				m_pOwner->GetTransform()->Translate(-overlapData.second, 0);
				myCollider->Update();
				break;
			}
			case ColliderComponent::OverlapData::Right:
			{
				m_pOwner->GetTransform()->Translate(overlapData.second, 0);
				myCollider->Update();
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
	if (m_Gravity == false)
		return;


}
