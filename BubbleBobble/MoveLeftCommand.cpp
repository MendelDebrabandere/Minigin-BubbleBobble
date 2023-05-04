#include "MoveLeftCommand.h"
#include "Timer.h"

void MoveLeftCommand::Execute()
{
	//Add movespeed and make frame independent movement
	float horMovement = dae::Time::GetInstance().GetDelta() * m_Speed;

	//Invert x-axis
	horMovement *= -1;

	//Transform GO
	auto transform = m_pGo->GetComponent<dae::Transform>();
	if (transform)
		transform->Translate(horMovement, 0);
}