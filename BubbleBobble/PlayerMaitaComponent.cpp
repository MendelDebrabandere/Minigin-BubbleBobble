#include "PlayerMaitaComponent.h"

#include "BubbleComponent.h"
#include "ColliderComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "Rock.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SpriteComponent.h"
#include "Timer.h"

float PlayerMaitaComponent::m_SpriteScale{ 4 };
dae::SpriteDataPreset PlayerMaitaComponent::m_Damaged{ false, 4, 8, 0.1f, 24, 28 };
dae::SpriteDataPreset PlayerMaitaComponent::m_Walking{ false, 4, 8, 0.3f, 8, 13 };
dae::SpriteDataPreset PlayerMaitaComponent::m_ThrowBoulder{ false, 4, 4, 0.2f, 7, 12 };

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
							dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/Damaged.wav", 100, 0);
							dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
							if (spriteComp)
							{
								spriteComp->SetAnimVariables(m_Damaged);
								spriteComp->Scale(m_SpriteScale);
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

		float elapsedSec = dae::Time::GetInstance().GetDelta();

		//If they are invulnerable, count down
		if (m_Invulnerable)
		{
			m_Timer += elapsedSec;

			if (m_Timer >= m_MaxInvulnerableTime)
			{
				m_Timer = 0.f;
				m_Invulnerable = false;
			}
		}

		auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
		spriteComp->SetRenderOffset(glm::vec2{ 0, 0 });
		if (m_Throwing)
		{

			m_RockThrowingTimer += elapsedSec;

			if (m_RockThrowingTimer >= 0.2f * 3.9f)
			{
				Rock::CreateRock(dae::SceneManager::GetInstance().GetActiveScene(), m_pOwner, m_pOwner->GetTransform()->GetFacingRight());
				spriteComp->SetAnimVariables(m_Walking);
				spriteComp->Scale(m_SpriteScale);
				m_Throwing = false;
				m_RockThrowingTimer = 0.f;
				break;
			}

			//Do sprite offset
			if (m_pOwner->GetTransform()->GetFacingRight() == false)
				spriteComp->SetRenderOffset(glm::vec2{ -spriteComp->GetSize().x / 2, 0 });

		}
		break;
	}
	case PlayerMaitaState::Hit:
	{
		DoRespawnLogic();

		auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
		spriteComp->SetRenderOffset(glm::vec2(0, 0));
		break;
	}
	}
}

void PlayerMaitaComponent::ThrowRock()
{
	if (m_CurrentState == PlayerMaitaState::Moving)
	{
		auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
		spriteComp->SetAnimVariables(m_ThrowBoulder);
		m_RockThrowingTimer = 0.f;
		spriteComp->Scale(m_SpriteScale);
		m_Throwing = true;

	}
}

PlayerMaitaComponent::PlayerMaitaState PlayerMaitaComponent::GetCurrState() const
{
	return m_CurrentState;
}

rapidjson::Value PlayerMaitaComponent::Serialize(rapidjson::Document::AllocatorType& allocator) const
{
	rapidjson::Value objectValue(rapidjson::kObjectType);

	// Serialize PlayerMaitaState as a string.
	switch (m_CurrentState) {
	case PlayerMaitaState::Moving:
		objectValue.AddMember("playerMaitaState", "Moving", allocator);
		break;
	case PlayerMaitaState::Hit:
		objectValue.AddMember("playerMaitaState", "Hit", allocator);
		break;
	}

	// Serialize other members.
	objectValue.AddMember("lastPosX", m_LastPos.x, allocator);
	objectValue.AddMember("lastPosY", m_LastPos.y, allocator);
	objectValue.AddMember("timer", m_Timer, allocator);
	objectValue.AddMember("maxRespawnTimer", m_MaxRespawmTimer, allocator);
	objectValue.AddMember("invulnerable", m_Invulnerable, allocator);
	objectValue.AddMember("maxInvulnerableTime", m_MaxInvulnerableTime, allocator);
	objectValue.AddMember("throwing", m_Throwing, allocator);
	objectValue.AddMember("rockThrowingTimer", m_RockThrowingTimer, allocator);

	return objectValue;
}


void PlayerMaitaComponent::Deserialize(const rapidjson::Value& value)
{
	// Deserialize PlayerMaitaState.
	if (value.HasMember("playerMaitaState")) {
		std::string stateStr = value["playerMaitaState"].GetString();
		if (stateStr == "Moving") m_CurrentState = PlayerMaitaState::Moving;
		else if (stateStr == "Hit") m_CurrentState = PlayerMaitaState::Hit;
	}

	// Deserialize other members.
	if (value.HasMember("lastPosX")) m_LastPos.x = value["lastPosX"].GetFloat();
	if (value.HasMember("lastPosY")) m_LastPos.y = value["lastPosY"].GetFloat();
	if (value.HasMember("timer")) m_Timer = value["timer"].GetFloat();
	if (value.HasMember("maxRespawnTimer")) m_MaxRespawmTimer = value["maxRespawnTimer"].GetFloat();
	if (value.HasMember("invulnerable")) m_Invulnerable = value["invulnerable"].GetBool();
	if (value.HasMember("maxInvulnerableTime")) m_MaxInvulnerableTime = value["maxInvulnerableTime"].GetFloat();
	if (value.HasMember("throwing")) m_Throwing = value["throwing"].GetBool();
	if (value.HasMember("rockThrowingTimer")) m_RockThrowingTimer = value["rockThrowingTimer"].GetFloat();
}



void PlayerMaitaComponent::UpdateAnimVariablesMoving()
{
	dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
	{
		//Check if the sprite should be paused or not depending on if it moved
		dae::Transform* transform = m_pOwner->GetTransform();

		glm::vec2 currPos = transform->GetLocalPosition();

		if (m_LastPos == currPos && m_Throwing == false)
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
			spriteComp->SetAnimVariables(m_Walking);
			spriteComp->Scale(m_SpriteScale);
			spriteComp->Pause(false);
		}


		m_pOwner->GetTransform()->SetWorldPosition(850, 700);

		m_Timer = 0.f;
		m_CurrentState = PlayerMaitaState::Moving;
		m_HealthChange.Notify(-1);

		m_Invulnerable = true;
	}
}
