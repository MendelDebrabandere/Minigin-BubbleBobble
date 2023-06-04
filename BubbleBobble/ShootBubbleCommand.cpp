#include "ShootBubbleCommand.h"

#include "AvatarComponent.h"
#include "Bubble.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "Timer.h"

void ShootBubbleCommand::Execute()
{
	AvatarComponent* avatarComp = m_pGo->GetComponent<AvatarComponent>();
	if (avatarComp->GetCurrState() == AvatarComponent::AvatarState::Moving)
	{
		dae::Scene* scene = dae::SceneManager::GetInstance().GetActiveScene();

		dae::SpriteComponent* spriteComp = m_pGo->GetComponent<dae::SpriteComponent>();
		if (avatarComp && spriteComp)
		{
			spriteComp->DoOnceAnim(0.1f, 7, 12);
			Bubble::CreateBubble(scene, m_pGo);
		}
	}
}
