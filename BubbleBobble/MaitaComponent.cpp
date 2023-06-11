#include "MaitaComponent.h"

#include "EnemyComponent.h"
#include "GameObject.h"
#include "Rock.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "Timer.h"

void MaitaComponent::Initialize()
{
	m_RockThrowingTimer = float(rand() % 3 + 5);
}

void MaitaComponent::Update()
{
	m_RockThrowingTimer -= dae::Time::GetInstance().GetDelta();

	auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();

	if (m_RockThrowingTimer < 0.f && spriteComp)
	{
		if (!m_Throwing)
		{
			spriteComp->SetAnimVariables(4, 4, 0.2f, 7, 12);
			m_RockThrowingTimer = 0.2f * 3.9f;
		}
		else
		{
			Rock::CreateRock(dae::SceneManager::GetInstance().GetActiveScene(), m_pOwner, m_pOwner->GetComponent<EnemyComponent>()->GetMoveRight());
			spriteComp->SetAnimVariables(4, 8, 0.3f, 8, 13);
			m_RockThrowingTimer = static_cast<float>(rand() % 3 + 5);
		}
		spriteComp->Scale(4);

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