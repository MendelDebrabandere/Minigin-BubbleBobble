#pragma once
#include "Scene.h"

class Avatar final
{
public:
	static dae::GameObject* CreateAvatar(dae::Scene* pScene, const glm::vec2& spawnPos, bool green, bool coop);
};

