#include "Platform.h"

#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"

using namespace dae;

GameObject* Platform::CreatePlatform(Scene* pScene, const glm::vec2& spawnPos)
{
	GameObject* pBlock{ pScene->CreateGameObject() };
	pBlock->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	SpriteComponent* spriteComp = pBlock->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Blocks.png");
	spriteComp->SetAnimVariables(1, 3, 1.f);
	spriteComp->Scale(4);
	spriteComp->Pause(true);

	auto colliderComp = pBlock->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	colliderComp->SetRendering(true);

	auto physicsComp = pBlock->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(false, true, true);
	physicsComp->SetPlatform(true);

	return pBlock;
}
