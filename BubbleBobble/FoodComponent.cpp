#include "FoodComponent.h"

#include "AvatarComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SpriteComponent.h"
#include "Timer.h"


void FoodComponent::Initialize()
{
	dae::ColliderComponent* myColl = m_pOwner->GetComponent<dae::ColliderComponent>();
	if (myColl)
	{
		myColl->SetOverlapFunction([this](dae::GameObject* overlappingActor)
			{
				if (m_CurrState == State::Points)
					return;

				//if its a player
				AvatarComponent* avatarComp = overlappingActor->GetComponent<AvatarComponent>();
				dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
				dae::PhysicsComponent* physComp = m_pOwner->GetComponent<dae::PhysicsComponent>();
				if (avatarComp && spriteComp && physComp)
				{
					avatarComp->PickedUpFood(m_MyType);
					m_CurrState = State::Points;
					dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/PickupFood.wav", 50, 0);
					//Set sprite variables
					switch(m_MyType)
					{
					case FoodType::Fries:
					{
						if (avatarComp->GetColor() == AvatarComponent::AvatarColor::green)
							spriteComp->SetAnimVariables(3, 2, 1.f, 3);
						else
							spriteComp->SetAnimVariables(3, 2, 1.f, 5);
						break;
					}
					case FoodType::Melon:
					{
						if (avatarComp->GetColor() == AvatarComponent::AvatarColor::green)
							spriteComp->SetAnimVariables(3, 2, 1.f, 2);
						else
							spriteComp->SetAnimVariables(3, 2, 1.f, 4);
						break;
					}
					}
					spriteComp->Scale(4);
					spriteComp->Pause(true);

					physComp->SetPhysicsSettings(false, false, false);
				}
			});
	}
}

void FoodComponent::Update()
{
	switch(m_CurrState)
	{
	case State::Food:
	{
		break;
	}
	case State::Points:
	{
		if (m_Timer >= 1.f)
		{
			m_pOwner->Destroy();
			return;
		}

		float deltaTime = dae::Time::GetInstance().GetDelta();
		m_Timer += deltaTime;

		m_pOwner->GetTransform()->Translate(glm::vec2(0, -deltaTime * 100.f));

		break;
	}
	}
}

void FoodComponent::SetFoodType(FoodType type)
{
	m_MyType = type;
}
