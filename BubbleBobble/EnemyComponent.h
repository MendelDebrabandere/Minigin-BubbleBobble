#pragma once
#include "Component.h"

class EnemyComponent : public dae::Component
{
public:
	EnemyComponent() = default;
	virtual ~EnemyComponent() = default;

	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;

	void Update() override;

private:

};
