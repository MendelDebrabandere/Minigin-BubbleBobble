#pragma once
#include "Component.h"

class FoodComponent : public dae::Component
{
public:
	enum class FoodType
	{
		Melon,
		Fries
	};

	FoodComponent() = default;
	virtual ~FoodComponent() = default;

	FoodComponent(const FoodComponent& other) = delete;
	FoodComponent(FoodComponent&& other) = delete;
	FoodComponent& operator=(const FoodComponent& other) = delete;
	FoodComponent& operator=(FoodComponent&& other) = delete;

	void Initialize() override;
	void Update() override;

	void SetFoodType(FoodType type);

private:
	FoodType m_MyType;
};
