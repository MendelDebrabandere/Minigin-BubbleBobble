#include "JumpCommand.h"
#include "ServiceLocator.h"
#include "PhysicsComponent.h"
#include "SoundSystem.h"

void JumpCommand::Execute()
{
	auto physicsComp = m_pGo->GetComponent<dae::PhysicsComponent>();

	if (physicsComp == nullptr)
		return;

	if (physicsComp->GetGrounded())
	{
		physicsComp->Jump(m_Speed);
		dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/TestEffect.wav", 50, 0);
	}
}
