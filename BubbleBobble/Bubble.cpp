#include "Bubble.h"

#include "BubbleFlyingComponent.h"
#include "ColliderComponent.h"
#include "JumpCommand.h"
#include "SpriteComponent.h"
#include "GameObject.h"

using namespace dae;

GameObject* Bubble::CreateBubble(Scene* pScene, const GameObject* pShooterObj)
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
	spriteComp->SetAnimVariables(4, 3, 0.3f, 6, 9);
	spriteComp->Scale(4);

	BubbleFlyingComponent* flyingComp = pBubble->AddComponent<BubbleFlyingComponent>();
	flyingComp->SetShootDirection(facingRight);

	return pBubble;
}
