#pragma once
#include "Scene.h"

class Bubble final
{
public:
	static dae::GameObject* CreateBubble(dae::Scene* pScene, const dae::GameObject* pShooterObj);
};

