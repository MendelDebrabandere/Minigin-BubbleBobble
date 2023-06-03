#include "Bubble.h"

#include "ColliderComponent.h"
#include "InputManager.h"
#include "JumpCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"

using namespace dae;

GameObject* Bubble::CreateBubble(Scene* pScene, const glm::vec2& spawnPos)
{
	GameObject* pBubble{ pScene->CreateGameObject() };
	pBubble->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	auto spriteComp = pBubble->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Bubble.png");
	spriteComp->SetAnimVariables(4, 4, 0.3f, 6, 9);
	spriteComp->Scale(4);


	return pBubble;
}