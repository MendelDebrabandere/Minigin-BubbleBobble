#include "MoveRightCommand.h"
#include "Timer.h"

void MoveRightCommand::Execute()
{
	//Add movespeed and make frame independent movement
	float horMovement = dae::Time::GetInstance().GetDelta() * m_Speed;

	//Transform GO
	auto transform = m_pGo->GetComponent<dae::Transform>();
	if (transform)
		transform->Translate(horMovement, 0);
}