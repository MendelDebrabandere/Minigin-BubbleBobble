#pragma once
#include "Component.h"

class FoodComponent final : public dae::Component
{
public:
	enum class FoodType
	{
		Melon,
		Fries
	};

	FoodComponent() = default;
	~FoodComponent() override;

	FoodComponent(const FoodComponent& other) = delete;
	FoodComponent(FoodComponent&& other) = delete;
	FoodComponent& operator=(const FoodComponent& other) = delete;
	FoodComponent& operator=(FoodComponent&& other) = delete;

	void Initialize() override;
	void Update() override;

	void SetFoodType(FoodType type);

private:
	enum class State
	{
		Food,
		Points
	};

	FoodType m_MyType{};
	State m_CurrState{ State::Food };

	float m_Timer{};
};
