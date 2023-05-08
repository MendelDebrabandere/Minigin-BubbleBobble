#include "JumpCommand.h"
#include "Timer.h"

void JumpCommand::Execute()
{
	//Add movespeed and make frame independent movement
	float vertMovement = dae::Time::GetInstance().GetDelta() * m_Speed;

	//Transform GO
	auto transform = m_pGo->GetComponent<dae::Transform>();
	if (transform)
		transform->Translate(0, -vertMovement);
}