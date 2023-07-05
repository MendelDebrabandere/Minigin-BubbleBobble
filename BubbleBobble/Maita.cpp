#include "Maita.h"

#include "ZenChan.h"

#include "ColliderComponent.h"
#include "EnemyComponent.h"
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
	spriteComp->SetAnimVariables(4, 8, 0.f); // Just rows and columns are important here, its used for hit box size calc
	spriteComp->Scale(4);

	auto colliderComp = pMiata->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	//colliderComp->SetRendering(true);

	auto physicsComp = pMiata->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(true, false, false);

	pMiata->AddComponent<EnemyComponent>();

	pMiata->AddComponent<MaitaComponent>();

	return pMiata;
}
