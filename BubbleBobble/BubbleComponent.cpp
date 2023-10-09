#include "BubbleComponent.h"
#include <SDL_stdinc.h>

#include "AvatarComponent.h"
#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "Food.h"
#include "Timer.h"
#include "Transform.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Maita.h"
#include "PhysicsComponent.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SpriteComponent.h"
#include "ZenChan.h"
#include "ZenChanComponent.h"

float BubbleComponent::m_SpriteScale{ 4 };
dae::SpriteDataPreset BubbleComponent::m_GreenZenChan{ false, 9, 4, 0.3f, 0, 4 };
dae::SpriteDataPreset BubbleComponent::m_BlueZenChan{ false, 9, 4, 0.3f, 4, 8 };
dae::SpriteDataPreset BubbleComponent::m_GreenMaita{ false, 9, 4, 0.3f, 8, 12 };
dae::SpriteDataPreset BubbleComponent::m_BlueMaita{ false, 9, 4, 0.3f, 12, 16 };
dae::SpriteDataPreset BubbleComponent::m_Pop{ true, 9, 4, 0.15f, 24, 26 };
dae::SpriteDataPreset BubbleComponent::m_DeadZenChan{ false, 9, 4, 0.1f, 28, 32 };
dae::SpriteDataPreset BubbleComponent::m_DeadMaita{ false, 9, 4, 0.1f, 32, 36 };

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
					dae::ColliderComponent* playerColl = overlappingActor->GetComponent<dae::ColliderComponent>();
					dae::ColliderComponent* myColl = m_pOwner->GetComponent<dae::ColliderComponent>();
					if (avatarComp && playerColl && myColl)
					{
						//if the player hits it from the top && the player is holding down spacebar
						if (myColl->IsOverlappingWithDirectional(playerColl).first == dae::ColliderComponent::OverlapData::Top
							&& dae::InputManager::GetInstance().IsKeyboardKeyDown('w'))
						{
							//set the physics to grounded so that the player can jump
							dae::PhysicsComponent* playerPhysics = overlappingActor->GetComponent<dae::PhysicsComponent>(); \
								playerPhysics->SetGrounded(true);
						}
						else
							Pop(true);
					}
					break;
				}
				default:
					break;
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
				else
					Maita::CreateMaita(dae::SceneManager::GetInstance().GetActiveScene(),
										m_pOwner->GetTransform()->GetWorldPosition());
			}

			Pop(false);
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
			//spawn a food
			auto scene = dae::SceneManager::GetInstance().GetActiveScene();
			if (m_ZenChan)
				Food::CreateFood(scene, m_pOwner, FoodComponent::FoodType::Melon);
			else
				Food::CreateFood(scene, m_pOwner, FoodComponent::FoodType::Fries);
			m_pOwner->Destroy();
		}

		if (abs(currPos.x - m_RandomGoToPos.x) <= 1.f == false)
			posDelta.x = m_RandomGoToPos.x - currPos.x < 0 ? -1.f : 1.f;
		if (abs(currPos.y - m_RandomGoToPos.y) <= 1.f == false)
			posDelta.y = m_RandomGoToPos.y - currPos.y < 0 ? -1.f : 1.f;

		posDelta *= 250 * deltaTime;

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

BubbleComponent::BubbleState BubbleComponent::GetState() const
{
	return m_CurrentState;
}

bool BubbleComponent::HasEnemyInside() const
{
	return m_HasEnemyInside;
}

void BubbleComponent::PickUpEnemy(dae::GameObject* go)
{
	m_HasEnemyInside = true;

	m_ZenChan = go->GetComponent<ZenChanComponent>();

	go->Destroy();
	dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
	{
		if (m_Blue)
		{
			if (m_ZenChan)
				spriteComp->SetAnimVariables(m_BlueZenChan);
			else
				spriteComp->SetAnimVariables(m_BlueMaita);
		}
		else
		{
			if (m_ZenChan)
				spriteComp->SetAnimVariables(m_GreenZenChan);
			else
				spriteComp->SetAnimVariables(m_GreenMaita);
		}
		spriteComp->Scale(m_SpriteScale);
	}
}

void BubbleComponent::Pop(bool byPlayer)
{
	auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (m_HasEnemyInside && byPlayer)
	{
		m_CurrentState = BubbleState::EnemyDying;
		dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/PopBubbleWithEnemy.wav", 100, 0);

		//Make death sprite animation
		if (spriteComp)
		{
			if (m_ZenChan)
				spriteComp->SetAnimVariables(m_DeadZenChan);
			else
				spriteComp->SetAnimVariables(m_DeadMaita);
			spriteComp->Scale(m_SpriteScale);
			m_Timer = 0.f;
			m_RandomGoToPos = glm::vec2{ 100 + rand() % 600, 100 + rand() % 600 };
		}
	}
	else
	{
		m_CurrentState = BubbleState::Popping;
		if (spriteComp)
			spriteComp->SetAnimVariables(m_Pop);
	}
}

void BubbleComponent::SetBlue(bool value)
{
	m_Blue = value;
}

rapidjson::Value BubbleComponent::Serialize(rapidjson::Document::AllocatorType& allocator) const
{
	rapidjson::Value objectValue(rapidjson::kObjectType);

	// Serialize BubbleState as a string.
	switch (m_CurrentState) {
	case BubbleState::Shooting:
		objectValue.AddMember("state", "Shooting", allocator);
		break;
	case BubbleState::Hovering:
		objectValue.AddMember("state", "Hovering", allocator);
		break;
	case BubbleState::ReachedTop:
		objectValue.AddMember("state", "ReachedTop", allocator);
		break;
	case BubbleState::Popping:
		objectValue.AddMember("state", "Popping", allocator);
		break;
	case BubbleState::EnemyDying:
		objectValue.AddMember("state", "EnemyDying", allocator);
		break;
	}

	// Serialize other members.
	objectValue.AddMember("directionRight", m_DirectionRight, allocator);
	objectValue.AddMember("hasEnemyInside", m_HasEnemyInside, allocator);
	objectValue.AddMember("zenChan", m_ZenChan, allocator);
	objectValue.AddMember("randomGoToPosX", m_RandomGoToPos.x, allocator);
	objectValue.AddMember("randomGoToPosY", m_RandomGoToPos.y, allocator);
	objectValue.AddMember("blue", m_Blue, allocator);

	return objectValue;
}


void BubbleComponent::Deserialize(const rapidjson::Value& value)
{
	// Deserialize BubbleState.
	std::string stateStr = value["state"].GetString();
	if (stateStr == "Shooting") m_CurrentState = BubbleState::Shooting;
	else if (stateStr == "Hovering") m_CurrentState = BubbleState::Hovering;
	else if (stateStr == "ReachedTop") m_CurrentState = BubbleState::ReachedTop;
	else if (stateStr == "Popping") m_CurrentState = BubbleState::Popping;
	else if (stateStr == "EnemyDying") m_CurrentState = BubbleState::EnemyDying;

	// Deserialize other members.
	if (value.HasMember("directionRight")) m_DirectionRight = value["directionRight"].GetBool();
	if (value.HasMember("hasEnemyInside")) m_HasEnemyInside = value["hasEnemyInside"].GetBool();
	if (value.HasMember("zenChan")) m_ZenChan = value["zenChan"].GetBool();
	if (value.HasMember("randomGoToPosX") && value.HasMember("randomGoToPosY")) {
		m_RandomGoToPos.x = value["randomGoToPosX"].GetFloat();
		m_RandomGoToPos.y = value["randomGoToPosY"].GetFloat();
	}
	if (value.HasMember("blue")) m_Blue = value["blue"].GetBool();

}

