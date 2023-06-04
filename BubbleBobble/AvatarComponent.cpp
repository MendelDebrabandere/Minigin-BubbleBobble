#include "AvatarComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "SpriteComponent.h"

void AvatarComponent::Update()
{
	//Check if the sprite should be paused or not
	dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
	{
		dae::Transform* transform = m_pOwner->GetTransform();

		glm::vec2 currPos = transform->GetLocalPosition();

		if (m_LastPos == currPos)
			spriteComp->Pause(true);
		else
		{
			spriteComp->Pause(false);
			//Check if it should be flipped
			if (currPos.x > m_LastPos.x)
			{
				spriteComp->FlipTexture(true);
			}
			else if (currPos.x < m_LastPos.x)
			{
				spriteComp->FlipTexture(false);
			}
		}
		m_LastPos = currPos;
	}
}

AvatarState AvatarComponent::GetCurrState() const
{
	return m_CurrentState;
}
