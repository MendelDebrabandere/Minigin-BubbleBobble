#include "JumpCommand.h"

#include "AvatarComponent.h"
#include "ServiceLocator.h"
#include "PhysicsComponent.h"
#include "SoundSystem.h"

void JumpCommand::Execute()
{
	AvatarComponent* avatarComp = m_pGo->GetComponent<AvatarComponent>();
	if (avatarComp->GetCurrState() == AvatarComponent::AvatarState::Moving)
	{
		auto physicsComp = m_pGo->GetComponent<dae::PhysicsComponent>();

		if (physicsComp == nullptr)
			return;

		if (physicsComp->GetCollisionState().BottomCollision)
		{
			physicsComp->Jump(m_Speed);
			dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/TestEffect.wav", 50, 0);
		}
	}
}
