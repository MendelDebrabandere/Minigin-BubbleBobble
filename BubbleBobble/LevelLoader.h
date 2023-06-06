#pragma once
#include "Scene.h"

class LevelLoader final
{
public:
	static void LoadLevel(dae::Scene* pScene, int number, bool loadAvatar);
};

