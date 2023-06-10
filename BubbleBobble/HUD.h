#pragma once
#include "PlayerMaitaComponent.h"
#include "Scene.h"

class AvatarComponent;

class HUD final
{
public:
	static dae::GameObject* CreateHUD(dae::Scene* pScene, AvatarComponent* avatarComp, PlayerMaitaComponent* maitaComp = nullptr);
};
