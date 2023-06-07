#include "ZenChanComponent.h"

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "Timer.h"

void ZenChanComponent::Update()
{
	//get data variables
	dae::Transform* transform = m_pOwner->GetTransform();
	dae::PhysicsComponent* physComp = m_pOwner->GetComponent< dae::PhysicsComponent>();
	float deltaTime = dae::Time::GetInstance().GetDelta();

	glm::vec2 moveDelta{};

	m_ChangeWalkDirTimer -= deltaTime;

	switch (m_CurrBehavior)
	{
	case BehaviorState::Wander:
	{
		//Do jumping cooldown logic
		if (m_JumpingCooldown > 0.f)
		{
			m_JumpingCooldown -= deltaTime;
		}
		else
		{
			//making some random stuff for the jump timings
			switch (rand() % 3)
			{
			case 0:
				m_JumpingCooldown = 0.82f;
				break;
			case 1:
				m_JumpingCooldown = 2.74f;
				break;
			case 2:
				m_JumpingCooldown = 2.31f;
				physComp->Jump(m_JumpSpeed);
				break;
			}
		}

		//change direction depending on timer
		if (m_ChangeWalkDirTimer < 0.f)
		{
			m_WalkingRight = !m_WalkingRight;
			m_ChangeWalkDirTimer = float(rand() % 5 + 5);
		}

		auto collisionState = physComp->GetCollisionState();
		//if it is falling, dont move
		if (collisionState.BottomCollision == false)
		{
			m_CurrBehavior = BehaviorState::Jumping; //(falling)
			break;
		}

		//Swap walkingDirection if it hits a wall
		if (collisionState.LeftCollision || collisionState.RightCollision)
		{
			m_WalkingRight = !m_WalkingRight;
		}

		//move
		int moveDir = m_WalkingRight ? 1 : -1;
		moveDelta.x = m_WalkingSpeed * moveDir * deltaTime;

		break;
	}
	case BehaviorState::Jumping:
	{
		auto collisionState = physComp->GetCollisionState();
		//if it hits a floor
		if (collisionState.BottomCollision)
		{
			//50% chance of jumping again if they are low 
			if (rand() % 2 != 0 && m_pOwner->GetTransform()->GetWorldPosition().y >= 300)
				physComp->Jump(m_JumpSpeed);
			else
				m_CurrBehavior = BehaviorState::Wander; //(falling)
		}
		break;
	}
	}

	//Charging logic happens independent of state, it is outside of the switch
	m_ChargingTimer -= deltaTime;
	auto spriteComponent = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (m_Charging)
	{
		moveDelta.x *= 2.3f;
		if (m_ChargingTimer < 0.f)
		{
			//stop charging
			m_Charging = false;
			m_ChargingTimer = float(rand() % 10 + 7); //random time between 7-17 sec before charging again
			spriteComponent->SetAnimVariables(3, 8, 0.3f, 0, 4);
			spriteComponent->Scale(4);
		}
	}
	else
	{
		if (m_ChargingTimer < 0.f)
		{
			//start charging
			m_Charging = true;
			m_ChargingTimer = float(rand() % 5 + 4); //random time between 4-9 sec before stopping
			spriteComponent->SetAnimVariables(3, 8, 0.1f, 4, 8);
			spriteComponent->Scale(4);
		}
	}


	transform->Translate(moveDelta);

	auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
		spriteComp->FlipTexture(m_WalkingRight);

}
