#include "ShootBubbleCommand.h"

#include "AvatarComponent.h"
#include "Bubble.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "Timer.h"

void ShootBubbleCommand::Execute()
{
	dae::Scene* scene = dae::SceneManager::GetInstance().GetActiveScene();

	AvatarComponent* avatarComp = m_pGo->GetComponent<AvatarComponent>();
	dae::SpriteComponent* spriteComp = m_pGo->GetComponent<dae::SpriteComponent>();
	if (avatarComp && spriteComp)
	{
		if (avatarComp->GetCurrState() == AvatarState::Moving)
		{
			spriteComp->DoOnceAnim(0.1f, 7, 12);
			Bubble::CreateBubble(scene, m_pGo);
		}
	}
}