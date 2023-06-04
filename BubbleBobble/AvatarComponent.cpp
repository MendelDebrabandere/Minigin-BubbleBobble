#include "AvatarComponent.h"

#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "Timer.h"

void AvatarComponent::Update()
{
	switch(m_CurrentState)
	{
	case AvatarState::Moving:
	{
		UpdateAnimVariablesMoving();
		break;
	}
	case AvatarState::Hit:
	{
		DoRespawnLogic();
		break;
	}
	}
}

void AvatarComponent::FixedUpdate()
{
	switch (m_CurrentState)
	{
	case AvatarState::Moving:
	{
		DoEnemyHitDetection();
		break;
	}
	case AvatarState::Hit:
	{
		break;
	}
	}
}

AvatarComponent::AvatarState AvatarComponent::GetCurrState() const
{
	return m_CurrentState;
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

void AvatarComponent::DoEnemyHitDetection()
{
	if (m_Invulnerable == false)
	{
		//Do enemy hit detection
		dae::ColliderComponent* myColl = m_pOwner->GetComponent<dae::ColliderComponent>();
		if (myColl)
		{
			dae::Scene* scene = dae::SceneManager::GetInstance().GetActiveScene();

			//Check for collision with enemies
			for (auto& object : scene->GetAllObjects())
			{
				//if its an enemy
				EnemyComponent* enemyComp = object->GetComponent<EnemyComponent>();
				if (enemyComp)
				{
					dae::ColliderComponent* otherColl = object->GetComponent<dae::ColliderComponent>();
					if (otherColl)
					{
						//if they are overlapping
						const auto overlapData = myColl->IsOverlappingWith(otherColl);
						if (overlapData.first != dae::ColliderComponent::OverlapData::Not)
						{
							//Got hit by enemy
							m_CurrentState = AvatarState::Hit;
							dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
							if (spriteComp)
							{
								spriteComp->SetAnimVariables(3, 7, 0.1f, 14, 18);
								spriteComp->Scale(4);
							}
						}
					}
				}
			}
		}
	}
	else
	{
		float elapsedSec = dae::Time::GetInstance().GetDelta();
		m_Timer += elapsedSec;

		if (m_Timer >= m_MaxInvulnerableTime)
		{
			m_Timer = 0.f;
			m_Invulnerable = false;
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
			spriteComp->SetAnimVariables(3, 7, 0.1f, 0, 7);
			spriteComp->Scale(4);
		}

		m_pOwner->GetTransform()->SetWorldPosition(90, 640);

		m_Timer = 0.f;
		m_CurrentState = AvatarState::Moving;

		m_Invulnerable = true;
	}
}
