#include "AvatarComponent.h"

#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "RockComponent.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SpriteComponent.h"
#include "Timer.h"

void AvatarComponent::Initialize()
{
	//Set up enemy hit detection
	dae::ColliderComponent* myColl = m_pOwner->GetComponent<dae::ColliderComponent>();
	if (myColl)
	{
		myColl->SetOverlapFunction([this](dae::GameObject* overlappingActor)
			{
				//if the player isnt invulnerable
				if (m_Invulnerable == false && m_CurrentState == AvatarState::Moving)
				{
					//if its an enemy or a rock
					EnemyComponent* enemyComp = overlappingActor->GetComponent<EnemyComponent>();
					RockComponent* rockComp = overlappingActor->GetComponent<RockComponent>();
					if (enemyComp || rockComp)
					{
						//Got hit by enemy
						if (rockComp)
						{
							if (rockComp->CanDamage() == false)
								return;
							rockComp->Crash();
						}

						m_CurrentState = AvatarState::Hit;
						dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/Damaged.wav", 100, 0);

						dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
						if (spriteComp)
						{
							if (m_MyColor == AvatarColor::green)
								spriteComp->SetAnimVariables(6, 7, 0.1f, 14, 18);
							else
								spriteComp->SetAnimVariables(6, 7, 0.1f, 35, 39);
							spriteComp->Scale(4);
							spriteComp->Pause(false);
						}

					}
				}
			});
	}
}

void AvatarComponent::Update()
{
	switch(m_CurrentState)
	{
	case AvatarState::Moving:
	{
		UpdateAnimVariablesMoving();

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
	case AvatarState::Hit:
	{
		DoRespawnLogic();
		break;
	}
	}
}

AvatarComponent::AvatarState AvatarComponent::GetCurrState() const
{
	return m_CurrentState;
}

void AvatarComponent::SetColor(AvatarColor color)
{
	m_MyColor = color;
}

AvatarComponent::AvatarColor AvatarComponent::GetColor() const
{
	return m_MyColor;
}

void AvatarComponent::PickedUpFood(FoodComponent::FoodType type)
{
	m_FoodPickup.Notify(type);
}

void AvatarComponent::UpdateAnimVariablesMoving()
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

void AvatarComponent::DoRespawnLogic()
{
	float elapsedSec = dae::Time::GetInstance().GetDelta();
	m_Timer += elapsedSec;

	if (m_Timer >= m_MaxRespawmTimer)
	{
		//Respawn
		dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
		if (spriteComp)
		{
			if (m_MyColor == AvatarColor::green)
				spriteComp->SetAnimVariables(6, 7, 0.1f, 0, 7);
			else
				spriteComp->SetAnimVariables(6, 7, 0.1f, 21, 28);
			spriteComp->Scale(4);
			spriteComp->Pause(false);
		}


		if (m_MyColor == AvatarColor::green)
			m_pOwner->GetTransform()->SetWorldPosition(100, 700);
		else
			m_pOwner->GetTransform()->SetWorldPosition(850, 700);

		m_Timer = 0.f;
		m_CurrentState = AvatarState::Moving;
		m_HealthChange.Notify(-1);

		m_Invulnerable = true;
	}
}
