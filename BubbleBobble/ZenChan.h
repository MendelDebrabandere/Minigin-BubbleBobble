#pragma once
#include "Scene.h"

class ZenChan final
{
public:
	static dae::GameObject* CreateZenChan(dae::Scene* pScene, const glm::vec2& spawnPos);
};

