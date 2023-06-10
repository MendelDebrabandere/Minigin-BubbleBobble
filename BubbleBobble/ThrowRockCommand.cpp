#include "ThrowRockCommand.h"

#include "PlayerMaitaComponent.h"

void ThrowRockCommand::Execute()
{
	PlayerMaitaComponent* maitaComp = m_pGo->GetComponent<PlayerMaitaComponent>();

	float totalGameTime = dae::Time::GetInstance().GetTotal();

	//Attack cooldonw
	if (maitaComp && totalGameTime - m_LastTimeThrew > 1.5f)
	{
		maitaComp->ThrowRock();
		m_LastTimeThrew = totalGameTime;
	}
}
