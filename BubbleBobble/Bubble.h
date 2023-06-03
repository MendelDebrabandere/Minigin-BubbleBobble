#pragma once
#include "Scene.h"

class Bubble final
{
public:
	static dae::GameObject* CreateBubble(dae::Scene* pScene, const glm::vec2& spawnPos);
};

