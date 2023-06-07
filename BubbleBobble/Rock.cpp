#include "Rock.h"

#include "BubbleComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "RockComponent.h"

using namespace dae;

GameObject* Rock::CreateRock(Scene* pScene, const GameObject* transformingObj, bool rightDir)
{
	Transform* transform = transformingObj->GetTransform();
	glm::vec2 spawnPos = transform->GetWorldPosition();

	GameObject* pRock{ pScene->CreateGameObject() };
	pRock->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	SpriteComponent* spriteComp = pRock->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Rock.png");
	spriteComp->SetAnimVariables(2, 4, 0.2f, 0, 4);
	spriteComp->Scale(4);

	ColliderComponent* colliderComp = pRock->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	//colliderComp->SetRendering(true);

	PhysicsComponent* physicsComp = pRock->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(true, false, false);

	pRock->AddComponent<RockComponent>()->SetMoveRight(rightDir);

	return pRock;
}
