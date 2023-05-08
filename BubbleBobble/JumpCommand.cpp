#include "JumpCommand.h"

#include "PhysicsComponent.h"

void JumpCommand::Execute()
{
	auto physicsComp = m_pGo->GetComponent<dae::PhysicsComponent>();

	if (physicsComp == nullptr)
		return;

	if (physicsComp->GetGrounded())
	{
		physicsComp->Jump(1.f);
	}
}