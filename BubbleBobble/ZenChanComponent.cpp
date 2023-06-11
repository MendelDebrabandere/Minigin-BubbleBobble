#include "ZenChanComponent.h"

#include "EnemyComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Timer.h"


void ZenChanComponent::Initialize()
{
	m_ChargingTimer = static_cast<float>(rand() % 20 + 10);
}

void ZenChanComponent::Update()
{
	float deltaTime = dae::Time::GetInstance().GetDelta();

	auto enemyComp = m_pOwner->GetComponent<EnemyComponent>();
	if (enemyComp == nullptr)
		return;


	//Charging logic happens independent of state, it is outside of the switch
	m_ChargingTimer -= deltaTime;
	auto spriteComponent = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (m_Charging)
	{
		enemyComp->MultiplyMoveSpeed(2.3f);
		if (m_ChargingTimer < 0.f)
		{
			//stop charging
			m_Charging = false;
			m_ChargingTimer = static_cast<float>(rand() % 10 + 7); //random time between 7-17 sec before charging again
			spriteComponent->SetAnimVariables(4, 8, 0.3f, 0, 4);
			spriteComponent->Scale(4);
		}
	}
	else
	{
		enemyComp->ResetMoveSpeed();
		if (m_ChargingTimer < 0.f)
		{
			//start charging
			m_Charging = true;
			m_ChargingTimer = static_cast<float>(rand() % 5 + 4); //random time between 4-9 sec before stopping
			spriteComponent->SetAnimVariables(4, 8, 0.1f, 4, 8);
			spriteComponent->Scale(4);
		}
	}

}
