#include "Block.h"

#include "ColliderComponent.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"

using namespace dae;

GameObject* Block::CreateBlock(Scene* pScene, const glm::vec2& spawnPos)
{
	GameObject* pBlock{ pScene->CreateGameObject() };
	pBlock->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	SpriteComponent* spriteComp = pBlock->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Blocks.png");
	spriteComp->SetAnimVariables(1,3,1.f);
	spriteComp->Scale(4);
	spriteComp->Pause(true);

	auto colliderComp = pBlock->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	colliderComp->SetRendering(true);

	return pBlock;
}
