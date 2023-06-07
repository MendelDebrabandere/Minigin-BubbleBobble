#include "Rock.h"

#include "BubbleComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"

using namespace dae;

GameObject* Rock::CreateRock(Scene* pScene, const GameObject* transformingObj)
{
	Transform* transform = transformingObj->GetTransform();
	glm::vec2 spawnPos = transform->GetWorldPosition();

	GameObject* pFood{ pScene->CreateGameObject() };
	pFood->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	SpriteComponent* spriteComp = pFood->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Rock.png");
	spriteComp->SetAnimVariables(2, 4, 0.2f, 0, 4);
	spriteComp->Scale(4);

	ColliderComponent* colliderComp = pFood->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	//colliderComp->SetRendering(true);

	PhysicsComponent* physicsComp = pFood->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(true, false, false);


	return pFood;
}
