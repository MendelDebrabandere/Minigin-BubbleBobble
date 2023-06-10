#include "Bubble.h"

#include "AvatarComponent.h"
#include "BubbleComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"

using namespace dae;

GameObject* Bubble::CreateBubble(Scene* pScene, const GameObject* pShooterObj)
{
	auto avatarComp = pShooterObj->GetComponent<AvatarComponent>();
	if (avatarComp)
	{
		Transform* transform = pShooterObj->GetTransform();
		if (transform == nullptr)
			return nullptr;

		glm::vec2 spawnPos = transform->GetWorldPosition();
		bool facingRight = transform->GetFacingRight();

		GameObject* pBubble{ pScene->CreateGameObject() };
		pBubble->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

		SpriteComponent* spriteComp = pBubble->AddComponent<SpriteComponent>();
		spriteComp->SetTexture("Bubble.png");
		if (avatarComp->GetColor() == AvatarComponent::AvatarColor::blue)
			spriteComp->SetAnimVariables(9, 4, 0.3f, 20, 24);
		else
			spriteComp->SetAnimVariables(9, 4, 0.3f, 16, 20);
		spriteComp->Scale(4);

		ColliderComponent* colliderComp = pBubble->AddComponent<ColliderComponent>();
		colliderComp->SetSize(spriteComp->GetSize());
		//colliderComp->SetRendering(true);

		BubbleComponent* bubbleComp = pBubble->AddComponent<BubbleComponent>();
		bubbleComp->SetShootDirection(facingRight);

		if (avatarComp->GetColor() == AvatarComponent::AvatarColor::blue)
			bubbleComp->SetBlue(true);

		return pBubble;
	}
	return nullptr;
}
