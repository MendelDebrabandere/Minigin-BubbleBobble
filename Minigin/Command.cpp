#include "Command.h"
#include "HealthComponent.h"
#include "Timer.h"

using namespace dae;

#pragma region MoveCommands
void MoveUpCommand::Execute()
{
	//Add movespeed and make frame independent movement
	float vertMovement = Time::GetInstance().GetDelta() * m_Speed;

	//Invert y-axis
	vertMovement *= -1;

	//Transform GO
	auto transform = m_pGo->GetComponent<Transform>();
	if (transform)
		transform->Translate(0, vertMovement);
}

void MoveDownCommand::Execute()
{
	//Add movespeed and make frame independent movement
	float vertMovement = Time::GetInstance().GetDelta() * m_Speed;
	
	//Transform GO
	auto transform = m_pGo->GetComponent<Transform>();
	if (transform)
		transform->Translate(0, vertMovement);
}

void MoveLeftCommand::Execute()
{
	//Add movespeed and make frame independent movement
	float horMovement = Time::GetInstance().GetDelta() * m_Speed;

	//Invert x-axis
	horMovement *= -1;

	//Transform GO
	auto transform = m_pGo->GetComponent<Transform>();
	if (transform)
		transform->Translate(horMovement, 0);
}

void MoveRightCommand::Execute()
{
	//Add movespeed and make frame independent movement
	float horMovement = Time::GetInstance().GetDelta() * m_Speed;

	//Transform GO
	auto transform = m_pGo->GetComponent<Transform>();
	if (transform)
		transform->Translate(horMovement, 0);
}
#pragma endregion

void dae::DamageCommand::Execute()
{
	if (m_pGo)
	{
		const auto healthComp = m_pGo->GetComponent<HealthComponent>();
		if (healthComp)
			healthComp->DoDamage(m_Amount);
	}
}

