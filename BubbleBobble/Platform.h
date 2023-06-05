#pragma once
#include "Scene.h"

class Platform final
{
public:
	static dae::GameObject* CreatePlatform(dae::Scene* pScene, const glm::vec2& spawnPos, int level);
};
