#include "MoveRightCommand.h"

#include "AvatarComponent.h"
#include "Timer.h"

void MoveRightCommand::Execute()
{
	AvatarComponent* avatarComp = m_pGo->GetComponent<AvatarComponent>();
	if (avatarComp->GetCurrState() == AvatarComponent::AvatarState::Moving)
	{

		//Add movespeed and make frame independent movement
		float horMovement = dae::Time::GetInstance().GetDelta() * m_Speed;

		//Transform GO
		auto transform = m_pGo->GetComponent<dae::Transform>();
		if (transform)
			transform->Translate(horMovement, 0);
	}
}