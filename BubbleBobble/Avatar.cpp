#include "Avatar.h"

#include "ColliderComponent.h"
#include "InputManager.h"
#include "JumpCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "PhysicsComponent.h"
#include "ShootBubbleCommand.h"
#include "SpriteComponent.h"

using namespace dae;

GameObject* Avatar::CreateAvatar(Scene* pScene, const glm::vec2& spawnPos)
{
	GameObject* pAvatar{ pScene->CreateGameObject() };
	pAvatar->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	auto spriteComp = pAvatar->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Avatar.png");
	spriteComp->SetAnimVariables(3, 7, 0.3f, 0, 7);
	spriteComp->Scale(4);

	auto colliderComp = pAvatar->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	colliderComp->SetRendering(true);

	auto physicsComp = pAvatar->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(true, true, false);

	InputManager::GetInstance().AddKeyboardCommand('a', InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pAvatar, 200.f));
	InputManager::GetInstance().AddKeyboardCommand('d', InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pAvatar, 200.f));
	InputManager::GetInstance().AddKeyboardCommand('w', InputManager::InputType::Pressed, std::make_unique<JumpCommand>(pAvatar, -500.f));
	InputManager::GetInstance().AddKeyboardCommand(' ', InputManager::InputType::Pressed, std::make_unique<ShootBubbleCommand>(pAvatar));

	return pAvatar;
}
