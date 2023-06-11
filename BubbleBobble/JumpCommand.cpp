#include "JumpCommand.h"

#include "AvatarComponent.h"
#include "ServiceLocator.h"
#include "PhysicsComponent.h"
#include "PlayerMaitaComponent.h"
#include "SoundSystem.h"

void JumpCommand::Execute()
{
	AvatarComponent* avatarComp = m_pGo->GetComponent<AvatarComponent>();
	PlayerMaitaComponent* maitaComp = m_pGo->GetComponent<PlayerMaitaComponent>();
	if (avatarComp && avatarComp->GetCurrState() != AvatarComponent::AvatarState::Moving)
		return;
	if (maitaComp && maitaComp->GetCurrState() != PlayerMaitaComponent::PlayerMaitaState::Moving)
		return;
	
	auto physicsComp = m_pGo->GetComponent<dae::PhysicsComponent>();

	if (physicsComp == nullptr)
		return;

	if (physicsComp->GetCollisionState().BottomCollision)
	{
		physicsComp->Jump(m_Speed);
		dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/JumpEffect.wav", 50, 0);
	}
}
