#include "Food.h"

#include "BubbleComponent.h"
#include "ColliderComponent.h"
#include "FoodComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"

using namespace dae;

GameObject* Food::CreateFood(Scene* pScene, const GameObject* transformingObj, FoodComponent::FoodType /*type*/)
{
	Transform* transform = transformingObj->GetTransform();
	if (transform == nullptr)
		return nullptr;

	glm::vec2 spawnPos = transform->GetWorldPosition();

	GameObject* pFood{ pScene->CreateGameObject() };
	pFood->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	SpriteComponent* spriteComp = pFood->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Food.png");
	spriteComp->SetAnimVariables(1, 2, 1.f);
	spriteComp->Scale(4);

	ColliderComponent* colliderComp = pFood->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	colliderComp->SetRendering(true);

	PhysicsComponent* physicsComp = pFood->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(true, false, false);

	pFood->AddComponent<FoodComponent>();

	return pFood;
}
