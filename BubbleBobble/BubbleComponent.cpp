#include "BubbleComponent.h"
#include <SDL_stdinc.h>

#include "AvatarComponent.h"
#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "Timer.h"
#include "Transform.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "ZenChan.h"

void BubbleComponent::Initialize()
{
	dae::ColliderComponent* myColl = m_pOwner->GetComponent<dae::ColliderComponent>();
	if (myColl)
	{
		myColl->SetOverlapFunction([this](dae::GameObject* overlappingActor)
			{
				switch (m_CurrentState)
				{
				case BubbleState::Shooting:
				{
					//if it can pick up an enemy
					if (m_HasEnemyInside == false)
					{
						//if its an enemy
						EnemyComponent* enemyComp = overlappingActor->GetComponent<EnemyComponent>();
						if (enemyComp)
						{
							PickUpEnemy(overlappingActor);
						}
					}
					break;
				}
				case BubbleState::Hovering:
				case BubbleState::ReachedTop:
				{
					//if its a player
					AvatarComponent* avatarComp = overlappingActor->GetComponent<AvatarComponent>();
					if (avatarComp)
					{
						PopByPlayer(overlappingActor);
					}
					break;
				}
				}
			});
	}
}

void BubbleComponent::Update()
{
	//increment timer
	float deltaTime = dae::Time::GetInstance().GetDelta();
	m_Timer += deltaTime;

	//Get transform and position
	dae::Transform* pTransform{ m_pOwner->GetTransform() };
	const glm::vec2 currPos = pTransform->GetWorldPosition();

	//Move object
	glm::vec2 posDelta{};

	switch (m_CurrentState)
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
		{
			if (m_HasEnemyInside)
			{
				if (m_ZenChan)
					ZenChan::CreateZenChan(dae::SceneManager::GetInstance().GetActiveScene(),
											m_pOwner->GetTransform()->GetWorldPosition());
				else;
					//TODO: spawn a maita
			}

			m_pOwner->Destroy();
		}
		break;
	}
	case BubbleState::Popping:
	{
		auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
		if (spriteComp)
			if (spriteComp->IsDoingOnce() == false) //the do once explosion ended
				m_pOwner->Destroy();
		break;
	}
	case BubbleState::EnemyDying:
	{
		// By calculating the dotproduct with itself it basically returns the squaredMagnitude
		if (abs(currPos.x - m_RandomGoToPos.x) <= 1.f && abs(currPos.y - m_RandomGoToPos.y) <= 1.f)
		{
			//TODO: spawn a fruity
			m_pOwner->Destroy();
		}

		if (abs(currPos.x - m_RandomGoToPos.x) <= 1.f == false)
			posDelta.x = m_RandomGoToPos.x - currPos.x < 0 ? -1.f : 1.f;
		if (abs(currPos.y - m_RandomGoToPos.y) <= 1.f == false)
			posDelta.y = m_RandomGoToPos.y - currPos.y < 0 ? -1.f : 1.f;

		posDelta *= 100 * deltaTime;

		break;
	}
	}

	//Set transform
	pTransform->Translate(posDelta);

}

void BubbleComponent::SetShootDirection(bool right)
{
	m_DirectionRight = right;
}

void BubbleComponent::PickUpEnemy(dae::GameObject* go)
{
	m_HasEnemyInside = true;
	go->Destroy();
	dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
	{
		spriteComp->SetAnimVariables(6, 4, 0.3f, 0, 3);
		spriteComp->Scale(4);
	}
}

void BubbleComponent::PopByPlayer(dae::GameObject* )
{
	auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (m_HasEnemyInside)
	{
		//TODO: give player score
		m_CurrentState = BubbleState::EnemyDying;
		if (spriteComp)
		{
			spriteComp->SetAnimVariables(6, 4, 0.1f, 20, 24);
			spriteComp->Scale(4);
			m_Timer = 0.f;
			m_RandomGoToPos = glm::vec2{ 100 + rand() % 600, 100 + rand() % 600 };
		}
	}
	else
	{
		m_CurrentState = BubbleState::Popping;
		if (spriteComp)
			spriteComp->DoOnceAnim(0.15f, 16, 18);
	}
}
