#include "PlayerMaita.h"

#include "ZenChan.h"

#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "InputManager.h"
#include "JumpCommand.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "MaitaComponent.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"

using namespace dae;

GameObject* PlayerMaita::CreateMaita(Scene* pScene, const glm::vec2& spawnPos)
{
	GameObject* pMiata{ pScene->CreateGameObject() };
	pMiata->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	auto spriteComp = pMiata->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Enemies.png");
	spriteComp->SetAnimVariables(3, 8, 0.3f, 8, 13);
	spriteComp->Scale(4);

	auto colliderComp = pMiata->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());
	//colliderComp->SetRendering(true);

	auto physicsComp = pMiata->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(true, false, false);

	//controller
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadLeft, 0, InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pMiata, 200.f));
	InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::DPadRight, 0, InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pMiata, 200.f));
	//InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::ButtonA, 1, InputManager::InputType::Pressed, std::make_unique<JumpCommand>(pAvatar, -450.f));
	//InputManager::GetInstance().AddControllerCommand(XBox360Controller::ControllerButton::ButtonB, 0, InputManager::InputType::OnDown, std::make_unique<ShootBubbleCommand>(pAvatar));


	return pMiata;
}
