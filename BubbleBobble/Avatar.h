#pragma once
#include "Scene.h"

class Avatar final
{
public:
	static dae::GameObject* CreateAvatar(dae::Scene* pScene, glm::vec2 spawnPos);
};

