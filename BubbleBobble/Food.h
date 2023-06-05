#pragma once
#include "Scene.h"
#include "FoodComponent.h"

class Food final
{
public:

	static dae::GameObject* CreateFood(dae::Scene* pScene, const dae::GameObject* transformingObj, FoodComponent::FoodType type);
};

