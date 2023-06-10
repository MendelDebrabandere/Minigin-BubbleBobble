#include "PlayerMaitaComponent.h"

#include "BubbleComponent.h"
#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "RockComponent.h"
#include "SpriteComponent.h"
#include "Timer.h"

void PlayerMaitaComponent::Initialize()
{
	//Set up enemy hit detection
	dae::ColliderComponent* myColl = m_pOwner->GetComponent<dae::ColliderComponent>();
	if (myColl)
	{
		myColl->SetOverlapFunction([this](dae::GameObject* overlappingActor)
			{
				//if the player isnt invulnerable
				if (m_Invulnerable == false && m_CurrentState == PlayerMaitaState::Moving)
				{
					//if its a bubble
					BubbleComponent* bubbleComp = overlappingActor->GetComponent<BubbleComponent>();
					if (bubbleComp && bubbleComp->GetState() == BubbleComponent::BubbleState::Shooting)
					{
						bubbleComp->Pop(false);
						{
							m_CurrentState = PlayerMaitaState::Hit;
							m_HealthChange.Notify(-1);
							dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
							if (spriteComp)
							{
								spriteComp->SetAnimVariables(4, 8, 0.1f, 24, 28);
								spriteComp->Scale(4);
								spriteComp->Pause(false);
							}
						}
					}
					else if(bubbleComp && (bubbleComp->GetState() == BubbleComponent::BubbleState::Hovering || bubbleComp->GetState() == BubbleComponent::BubbleState::ReachedTop))
					{
						bubbleComp->Pop(false);
					}
				}
			});
	}
}

void PlayerMaitaComponent::Update()
{
	switch (m_CurrentState)
	{
	case PlayerMaitaState::Moving:
	{
		UpdateAnimVariablesMoving();
		break;
	}
	case PlayerMaitaState::Hit:
	{
		break;
	}
	}
}

void PlayerMaitaComponent::FixedUpdate()
{
	switch (m_CurrentState)
	{
	case PlayerMaitaState::Moving:
	{
		//If they are invulnerable, count down
		if (m_Invulnerable)
		{
			float elapsedSec = dae::Time::GetInstance().GetDelta();
			m_Timer += elapsedSec;

			if (m_Timer >= m_MaxInvulnerableTime)
			{
				m_Timer = 0.f;
				m_Invulnerable = false;
			}
		}
		break;
	}
	case PlayerMaitaState::Hit:
	{
		DoRespawnLogic();
		break;
	}
	}
}

PlayerMaitaComponent::PlayerMaitaState PlayerMaitaComponent::GetCurrState() const
{
	return m_CurrentState;
}


void PlayerMaitaComponent::UpdateAnimVariablesMoving()
{
	dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
	{
		//Check if the sprite should be paused or not depending on if it moved
		dae::Transform* transform = m_pOwner->GetTransform();

		glm::vec2 currPos = transform->GetLocalPosition();

		if (m_LastPos == currPos)
			spriteComp->Pause(true);
		else
		{
			spriteComp->Pause(false);
			//Check if it should be flipped
			if (currPos.x > m_LastPos.x)
			{
				spriteComp->FlipTexture(true);
			}
			else if (currPos.x < m_LastPos.x)
			{
				spriteComp->FlipTexture(false);
			}
		}
		m_LastPos = currPos;


		//If its unvulnerable make it flicker
		if (m_Invulnerable)
		{
			//flicker on and off 3 times per second
			int shouldFlicker = int(m_Timer * 6) % 2;
			spriteComp->ToggleVisuals(shouldFlicker);
		}
	}
}

void PlayerMaitaComponent::DoRespawnLogic()
{
	float elapsedSec = dae::Time::GetInstance().GetDelta();
	m_Timer += elapsedSec;

	if (m_Timer >= m_MaxRespawmTimer)
	{
		//Respawn
		dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
		if (spriteComp)
		{
			spriteComp->SetAnimVariables(4, 8, 0.1f, 8, 13);
			spriteComp->Scale(4);
			spriteComp->Pause(false);
		}


		m_pOwner->GetTransform()->SetWorldPosition(850, 700);

		m_Timer = 0.f;
		m_CurrentState = PlayerMaitaState::Moving;

		m_Invulnerable = true;
	}
}
