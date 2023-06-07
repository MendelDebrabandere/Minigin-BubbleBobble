#pragma once
#include "Scene.h"

class Rock final
{
public:

	static dae::GameObject* CreateRock(dae::Scene* pScene, const dae::GameObject* transformingObj, bool rightDir);
};

