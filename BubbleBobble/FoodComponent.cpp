#include "FoodComponent.h"

#include "AvatarComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"


void FoodComponent::Initialize()
{
	dae::ColliderComponent* myColl = m_pOwner->GetComponent<dae::ColliderComponent>();
	if (myColl)
	{
		myColl->SetOverlapFunction([this](dae::GameObject* overlappingActor)
			{
				//if its a player
				AvatarComponent* avatarComp = overlappingActor->GetComponent<AvatarComponent>();
				if (avatarComp)
				{
					//TODO: give player score
					switch (m_MyType)
					{
					case FoodType::Melon:
					{
						break;
					}
					case FoodType::Fries:
					{
						break;
					}
					}

					m_pOwner->Destroy();

				}
			});
	}
}

void FoodComponent::Update()
{
	
}

void FoodComponent::SetFoodType(FoodType type)
{
	m_MyType = type;
}
