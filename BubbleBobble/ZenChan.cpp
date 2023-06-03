#include "ZenChan.h"

#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "JumpCommand.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"

using namespace dae;

GameObject* ZenChan::CreateZenChan(Scene* pScene, const glm::vec2& spawnPos)
{
	GameObject* pZen{ pScene->CreateGameObject() };
	pZen->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	pZen->AddComponent<EnemyComponent>();

	auto spriteComp = pZen->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("ZenChan.png");
	spriteComp->SetAnimVariables(5, 4, 0.3f, 0, 4);
	spriteComp->Scale(4);

	auto colliderComp = pZen->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	colliderComp->SetRendering(true);

	auto physicsComp = pZen->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(true, true, false);

	return pZen;
}
