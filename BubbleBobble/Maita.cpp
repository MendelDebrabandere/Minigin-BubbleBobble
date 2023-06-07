#include "Maita.h"

#include "ZenChan.h"

#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "JumpCommand.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "MaitaComponent.h"

using namespace dae;

GameObject* Maita::CreateMaita(Scene* pScene, const glm::vec2& spawnPos)
{
	GameObject* pMiata{ pScene->CreateGameObject() };
	pMiata->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	auto spriteComp = pMiata->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Enemies.png");
	spriteComp->SetAnimVariables(3, 8, 0.3f, 8, 13);
	spriteComp->Scale(4);

	auto colliderComp = pMiata->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	colliderComp->SetRendering(true);

	auto physicsComp = pMiata->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(true, false, false);

	pMiata->AddComponent<EnemyComponent>();

	pMiata->AddComponent<MaitaComponent>();

	return pMiata;
}
