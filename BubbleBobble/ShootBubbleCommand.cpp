#include "ShootBubbleCommand.h"

#include "AvatarComponent.h"
#include "Bubble.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SpriteComponent.h"
#include "Timer.h"
#include "SoundSystem.h"

void ShootBubbleCommand::Execute()
{
	AvatarComponent* avatarComp = m_pGo->GetComponent<AvatarComponent>();
	dae::SpriteComponent* spriteComp = m_pGo->GetComponent<dae::SpriteComponent>();

	if (avatarComp && spriteComp)
	{
		//Dont shoot if he is already shooting / doing something else
		if (spriteComp->IsDoingOnce())
			return;

		if (avatarComp->GetCurrState() == AvatarComponent::AvatarState::Moving)
		{
			dae::Scene* scene = dae::SceneManager::GetInstance().GetActiveScene();
			Bubble::CreateBubble(scene, m_pGo);\
			dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/ShootBubbleEffect.wav", 50, 0);


			if (avatarComp->GetColor() == AvatarComponent::AvatarColor::green)
				spriteComp->DoOnceAnim(0.1f, 7, 12);
			else
				spriteComp->DoOnceAnim(0.1f, 28, 33);
		}
	}
}
