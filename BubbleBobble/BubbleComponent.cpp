#include "BubbleComponent.h"
#include <SDL_stdinc.h>

#include "AvatarComponent.h"
#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "Timer.h"
#include "Transform.h"
#include "GameObject.h"
#include "SpriteComponent.h"

void BubbleComponent::Initialize()
{
	dae::ColliderComponent* myColl = m_pOwner->GetComponent<dae::ColliderComponent>();
	if (myColl)
	{
		myColl->SetOverlapFunction([&](dae::GameObject* overlappingActor)
			{
				switch (m_CurrentState)
				{
				case BubbleState::Shooting:
				{
					//if its an enemy
					EnemyComponent* enemyComp = overlappingActor->GetComponent<EnemyComponent>();
					if (enemyComp)
					{
						PickUpEnemy(overlappingActor);
					}
					break;
				}
				case BubbleState::Hovering:
				case BubbleState::ReachedTop:
				{
					if (m_HasEnemyInside)
					{
						//if its a player
						AvatarComponent* avatarComp = overlappingActor->GetComponent<AvatarComponent>();
						if (avatarComp)
						{
							PopByPlayer(overlappingActor);
						}
					}
					break;
				}
				}
			});
	}
}

void BubbleComponent::Update()
{
	DoMovementLogic();
}

void BubbleComponent::SetShootDirection(bool right)
{
	m_DirectionRight = right;
}

void BubbleComponent::DoMovementLogic()
{
	//increment timer
	float deltaTime = dae::Time::GetInstance().GetDelta();
	m_Timer += deltaTime;

	//Get transform and position
	dae::Transform* pTransform{ m_pOwner->GetTransform() };
	const glm::vec2 currPos = pTransform->GetWorldPosition();

	//Move object
	glm::vec2 posDelta{};
	
	switch(m_CurrentState)
	{
	case BubbleState::Shooting:
	{
		//Move horizontally
		constexpr float horMoveSpeed{ 450 };
		posDelta.x = (m_DirectionRight ? horMoveSpeed * deltaTime : -horMoveSpeed * deltaTime);

		//Check if it goes out of bounds
		if (currPos.x <= 70 || currPos.x >= 890)
		{
			posDelta.x = 0;
			m_Timer = 1.f;
		}

		//Check if it was shooting for long enough
		if (m_Timer >= 0.5f)
		{
			m_CurrentState = BubbleState::Hovering;
		}

		break;
	}
	case BubbleState::Hovering:
	{
		//Move vertically
		constexpr float vertMoveSpeed{ 100 };
		posDelta.y = -vertMoveSpeed * deltaTime;

		//Check if it reached the top
		if (currPos.y <= 70)
		{
			m_CurrentState = BubbleState::ReachedTop;
			posDelta.y = 0;
			m_Timer = 0.f;
		}

		break;
	}
	case BubbleState::ReachedTop:
	{
		if (m_Timer >= 3.f)
			m_pOwner->Destroy();
		break;
	}
	}

	//Set transform
	pTransform->SetWorldPosition(currPos + posDelta);

}

void BubbleComponent::PickUpEnemy(dae::GameObject* go)
{
	m_HasEnemyInside = true;
	go->Destroy();
	dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
	{
		spriteComp->SetAnimVariables(4, 3, 0.3f, 0, 3);
		spriteComp->Scale(4);
	}
}

void BubbleComponent::PopByPlayer(dae::GameObject* )
{
	m_pOwner->Destroy();
}
