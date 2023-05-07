#include "Avatar.h"

#include "InputManager.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "ResourceManager.h"

using namespace dae;

GameObject* Avatar::CreateAvatar(Scene* pScene, const glm::vec2& spawnPos)
{
	GameObject* pAvatar{ pScene->CreateGameObject() };
	pAvatar->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	pAvatar->AddComponent<TextureComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("MainCharacter.png"));

	//TODO: pAvatar->AddComponent<ColliderComponent>();

	InputManager::GetInstance().AddKeyboardCommand('a', InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pAvatar, 200.f));
	InputManager::GetInstance().AddKeyboardCommand('d', InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pAvatar, 200.f));

	return pAvatar;
}
