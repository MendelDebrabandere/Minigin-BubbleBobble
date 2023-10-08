#include "EnemyComponent.h"

#include "AvatarComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "Timer.h"

void EnemyComponent::Initialize()
{
	m_WalkingRight = false;
	m_WalkingSpeed = 150.f;
	m_JumpingCooldown = 2;
	m_JumpSpeed = -450;
	m_ChangeWalkDirTimer = static_cast<float>(rand() % 2 + 3);

	// init avatar transform
	auto& allObjects = dae::SceneManager::GetInstance().GetActiveScene()->GetAllObjects();
	for (auto& obj : allObjects)
	{
		if (obj->GetComponent<AvatarComponent>())
		{
			m_pAvatarTransform = obj->GetTransform();
		}
	}
}

void EnemyComponent::Update()
{
	if (m_pAvatarTransform == nullptr)
	{
		Initialize();
	}

	//get data variables
	dae::Transform* transform = m_pOwner->GetTransform();
	glm::vec2 myPos = transform->GetWorldPosition();
	glm::vec2 avatarPos = m_pAvatarTransform->GetWorldPosition(); 
	glm::vec2 releativeAvatarPos{ avatarPos - myPos };
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
			if (releativeAvatarPos.y < -1.f)
			{
				//making some random stuff for the jump timings
				switch (rand() % 3)
				{
				case 0:
					m_JumpingCooldown = 0.62f;
					break;
				case 1:
					m_JumpingCooldown = 1.34f;
					break;
				case 2:
					m_JumpingCooldown = 1.11f;
					physComp->Jump(m_JumpSpeed);
					break;
				default:
					break;
				}
			}
		}

		//change direction depending on timer
		if (m_ChangeWalkDirTimer < 0.f)
		{
			if (releativeAvatarPos.x < 0)
				m_WalkingRight = false;
			else
				m_WalkingRight = true;
			m_ChangeWalkDirTimer = static_cast<float>(rand() % 2 + 3);
		}

		auto collisionState = physComp->GetCollisionState();
		//if it is falling, change behavior
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
		float moveDir = m_WalkingRight ? 1.f : -1.f;
		moveDelta.x = m_WalkingSpeed * moveDir * deltaTime;

		break;
	}
	case BehaviorState::Jumping:
	{
		auto collisionState = physComp->GetCollisionState();
		//if it hits a floor
		if (collisionState.BottomCollision)
		{
			//50% chance of jumping again if player is above them
			if (rand() % 3 == 0 && releativeAvatarPos.y < -10)
				physComp->Jump(m_JumpSpeed);
			else
				m_CurrBehavior = BehaviorState::Wander; //(falling)
		}
		break;
	}
	}

	transform->Translate(moveDelta);

	auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
		spriteComp->FlipTexture(m_WalkingRight);


}


void EnemyComponent::MultiplyMoveSpeed(float value)
{
	ResetMoveSpeed();
	m_WalkingSpeed *= value;
}

void EnemyComponent::ResetMoveSpeed()
{
	m_WalkingSpeed = 150.f;
}

bool EnemyComponent::GetMoveRight() const
{
	return m_WalkingRight;
}

rapidjson::Value EnemyComponent::Serialize(rapidjson::Document::AllocatorType& allocator) const
{
	rapidjson::Value obj(rapidjson::kObjectType);

	// Serialize basic types
	obj.AddMember("BehaviorState", static_cast<int>(m_CurrBehavior), allocator);
	obj.AddMember("WalkingRight", m_WalkingRight, allocator);
	obj.AddMember("WalkingSpeed", m_WalkingSpeed, allocator);
	obj.AddMember("JumpingCooldown", m_JumpingCooldown, allocator);
	obj.AddMember("JumpSpeed", m_JumpSpeed, allocator);
	obj.AddMember("ChangeWalkDirTimer", m_ChangeWalkDirTimer, allocator);

	return obj;
}


void EnemyComponent::Deserialize(const rapidjson::Value& obj)
{
	if (obj.HasMember("BehaviorState"))
		m_CurrBehavior = static_cast<BehaviorState>(obj["BehaviorState"].GetInt());

	if (obj.HasMember("WalkingRight"))
		m_WalkingRight = obj["WalkingRight"].GetBool();

	if (obj.HasMember("WalkingSpeed"))
		m_WalkingSpeed = obj["WalkingSpeed"].GetFloat();

	if (obj.HasMember("JumpingCooldown"))
		m_JumpingCooldown = obj["JumpingCooldown"].GetFloat();

	if (obj.HasMember("JumpSpeed"))
		m_JumpSpeed = obj["JumpSpeed"].GetFloat();

	if (obj.HasMember("ChangeWalkDirTimer"))
		m_ChangeWalkDirTimer = obj["ChangeWalkDirTimer"].GetFloat();
}

