#include "Command.h"
#include "InputManager.h"
#include "Time.h"

using namespace dae;

#pragma region MoveCommands
void MoveUpCommand::Execute()
{
	//Add movespeed and make frame independent movement
	float vertMovement = Time::GetInstance().GetDelta() * m_Speed;

	//Invert y-axis
	vertMovement *= -1;

	//Transform GO
	m_pGo->GetComponent<Transform>()->Translate(0, vertMovement);
}

void MoveDownCommand::Execute()
{
	//Add movespeed and make frame independent movement
	float vertMovement = Time::GetInstance().GetDelta() * m_Speed;
	
	//Transform GO
	m_pGo->GetComponent<Transform>()->Translate(0, vertMovement);
}

void MoveLeftCommand::Execute()
{
	//Add movespeed and make frame independent movement
	float horMovement = Time::GetInstance().GetDelta() * m_Speed;

	//Invert x-axis
	horMovement *= -1;

	//Transform GO
	m_pGo->GetComponent<Transform>()->Translate(horMovement, 0);
}

void MoveRightCommand::Execute()
{
	//Add movespeed and make frame independent movement
	float horMovement = Time::GetInstance().GetDelta() * m_Speed;

	//Transform GO
	m_pGo->GetComponent<Transform>()->Translate(horMovement, 0);
}
#pragma endregion
