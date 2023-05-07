#include "Avatar.h"

#include "InputManager.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"

using namespace dae;

GameObject* Avatar::CreateAvatar(Scene* pScene, const glm::vec2& spawnPos)
{
	GameObject* pAvatar{ pScene->CreateGameObject() };
	pAvatar->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	auto spriteComp = pAvatar->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Bubble.png");
	spriteComp->SetAnimVariables(3, 7, 0.3f, 0, 7);
	spriteComp->Scale(4);

	//TODO: pAvatar->AddComponent<ColliderComponent>();

	InputManager::GetInstance().AddKeyboardCommand('a', InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pAvatar, 200.f));
	InputManager::GetInstance().AddKeyboardCommand('d', InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pAvatar, 200.f));

	return pAvatar;
}
