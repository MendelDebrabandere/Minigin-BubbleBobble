#include "ZenChan.h"

#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "JumpCommand.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "ZenChanComponent.h"

using namespace dae;

GameObject* ZenChan::CreateZenChan(Scene* pScene, const glm::vec2& spawnPos)
{
	GameObject* pZen{ pScene->CreateGameObject() };
	pZen->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	auto spriteComp = pZen->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Enemies.png");
	spriteComp->SetAnimVariables(3, 8, 0.3f, 0, 4);
	spriteComp->Scale(4);

	auto colliderComp = pZen->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	colliderComp->SetRendering(true);

	auto physicsComp = pZen->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(true, false, false);

	pZen->AddComponent<EnemyComponent>();

	pZen->AddComponent<ZenChanComponent>();

	return pZen;
}
