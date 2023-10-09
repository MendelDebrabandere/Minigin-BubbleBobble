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


float AvatarComponent::m_SpriteScale{ 4 };
dae::SpriteDataPreset AvatarComponent::m_GreenWalking{ false, 6, 7, 0.1f, 0, 7 };
dae::SpriteDataPreset AvatarComponent::m_GreenDamaged{ false, 6, 7, 0.1f, 14, 18 };
dae::SpriteDataPreset AvatarComponent::m_BlueWalking{ false, 6, 7, 0.1f, 21, 28 };
dae::SpriteDataPreset AvatarComponent::m_BlueDamaged{ false, 6, 7, 0.1f, 35, 39 };


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
								spriteComp->SetAnimVariables(m_GreenDamaged);
							else
								spriteComp->SetAnimVariables(m_BlueDamaged);
							spriteComp->Scale(m_SpriteScale);
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

rapidjson::Value AvatarComponent::Serialize(rapidjson::Document::AllocatorType& allocator) const
{
	rapidjson::Value obj(rapidjson::kObjectType);

	// Serialize basic types
	obj.AddMember("CurrentState", rapidjson::Value(static_cast<int>(m_CurrentState)), allocator);
	obj.AddMember("LastPos", rapidjson::Value(rapidjson::kArrayType).PushBack(m_LastPos.x, allocator).PushBack(m_LastPos.y, allocator), allocator);
	obj.AddMember("Timer", m_Timer, allocator);
	obj.AddMember("MaxRespawmTimer", m_MaxRespawmTimer, allocator);
	obj.AddMember("Invulnerable", m_Invulnerable, allocator);
	obj.AddMember("MaxInvulnerableTime", m_MaxInvulnerableTime, allocator);
	obj.AddMember("MyColor", rapidjson::Value(static_cast<int>(m_MyColor)), allocator);

	return obj;
}


void AvatarComponent::Deserialize(const rapidjson::Value& obj)
{
	if (obj.HasMember("CurrentState"))
		m_CurrentState = static_cast<AvatarState>(obj["CurrentState"].GetInt());

	if (obj.HasMember("LastPos") && obj["LastPos"].IsArray())
	{
		m_LastPos.x = obj["LastPos"][0].GetFloat();
		m_LastPos.y = obj["LastPos"][1].GetFloat();
	}

	if (obj.HasMember("Timer"))
		m_Timer = obj["Timer"].GetFloat();

	if (obj.HasMember("MaxRespawmTimer"))
		m_MaxRespawmTimer = obj["MaxRespawmTimer"].GetFloat();

	if (obj.HasMember("Invulnerable"))
		m_Invulnerable = obj["Invulnerable"].GetBool();

	if (obj.HasMember("MaxInvulnerableTime"))
		m_MaxInvulnerableTime = obj["MaxInvulnerableTime"].GetFloat();

	if (obj.HasMember("MyColor"))
		m_MyColor = static_cast<AvatarColor>(obj["MyColor"].GetInt());
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
				spriteComp->SetAnimVariables(m_GreenWalking);
			else
				spriteComp->SetAnimVariables(m_BlueWalking);
			spriteComp->Scale(m_SpriteScale);
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
