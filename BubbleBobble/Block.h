#pragma once
#include "Scene.h"

class Block final
{
public:
	static dae::GameObject* CreateBlock(dae::Scene* pScene, const glm::vec2& spawnPos, int level);
};
