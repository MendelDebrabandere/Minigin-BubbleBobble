#include "MoveLeftCommand.h"

#include "AvatarComponent.h"
#include "PlayerMaitaComponent.h"
#include "Timer.h"

void MoveLeftCommand::Execute()
{
	AvatarComponent* avatarComp = m_pGo->GetComponent<AvatarComponent>();
	PlayerMaitaComponent* maitaComp = m_pGo->GetComponent<PlayerMaitaComponent>();
	if (avatarComp)
	{
		if (avatarComp->GetCurrState() == AvatarComponent::AvatarState::Moving)
		{
			Move();
		}
	}
	else if (maitaComp)
	{
		if (maitaComp->GetCurrState() == PlayerMaitaComponent::PlayerMaitaState::Moving)
		{
			Move();
		}
	}

}

void MoveLeftCommand::Move()
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
