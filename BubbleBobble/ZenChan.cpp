#include "ZenChan.h"

#include "ColliderComponent.h"
#include "EnemyComponent.h"
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
	spriteComp->SetAnimVariables(4, 8, 0.f); // Just rows and columns are important here, its used for hit box size calc
	spriteComp->Scale(4);

	auto colliderComp = pZen->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	//colliderComp->SetRendering(true);

	auto physicsComp = pZen->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(true, false, false);

	pZen->AddComponent<EnemyComponent>();

	pZen->AddComponent<ZenChanComponent>();

	return pZen;
}
