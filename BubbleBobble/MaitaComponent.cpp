#include "MaitaComponent.h"

#include "EnemyComponent.h"
#include "GameObject.h"
#include "Rock.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "Timer.h"

float MaitaComponent::m_SpriteScale{4};
dae::SpriteDataPreset MaitaComponent::m_WalkingPreset{false, 4, 8, 0.3f, 8, 13};
dae::SpriteDataPreset MaitaComponent::m_AttackingPreset{false, 4, 4, 0.2f, 7, 12};

MaitaComponent::MaitaComponent()
	: m_RockThrowingTimer{ static_cast<float>(rand() % 3 + 5) }
{
}

void MaitaComponent::Initialize()
{
	dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
	{
		spriteComp->SetAnimVariables(m_WalkingPreset);
		spriteComp->Scale(m_SpriteScale);
	}
}

void MaitaComponent::Update()
{
	m_RockThrowingTimer -= dae::Time::GetInstance().GetDelta();

	auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();

	if (m_RockThrowingTimer < 0.f && spriteComp)
	{
		if (!m_Throwing)
		{
			spriteComp->SetAnimVariables(m_AttackingPreset);
			m_RockThrowingTimer = 0.2f * 3.9f;
		}
		else
		{
			Rock::CreateRock(dae::SceneManager::GetInstance().GetActiveScene(), m_pOwner, m_pOwner->GetComponent<EnemyComponent>()->GetMoveRight());
			spriteComp->SetAnimVariables(m_WalkingPreset);
			m_RockThrowingTimer = static_cast<float>(rand() % 3 + 5);
		}
		spriteComp->Scale(m_SpriteScale);

		m_Throwing = !m_Throwing;
	}

	//Do sprite offset
	spriteComp->SetRenderOffset(glm::vec2{ 0, 0 });
	if (m_Throwing)
	{
		if (m_pOwner->GetComponent<EnemyComponent>()->GetMoveRight() == false)
			spriteComp->SetRenderOffset(glm::vec2{ -spriteComp->GetSize().x /2, 0 });
	}
}

rapidjson::Value MaitaComponent::Serialize(rapidjson::Document::AllocatorType& allocator) const
{
	rapidjson::Value obj(rapidjson::kObjectType);

	// Serialize basic types
	obj.AddMember("Throwing", m_Throwing, allocator);
	obj.AddMember("RockThrowingTimer", m_RockThrowingTimer, allocator);

	return obj;
}

void MaitaComponent::Deserialize(const rapidjson::Value& obj)
{
	if (obj.HasMember("Throwing"))
		m_Throwing = obj["Throwing"].GetBool();

	if (obj.HasMember("RockThrowingTimer"))
		m_RockThrowingTimer = obj["RockThrowingTimer"].GetFloat();
}

