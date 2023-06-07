#pragma once
#include "Component.h"

class MaitaComponent : public dae::Component
{
public:
	MaitaComponent() = default;
	virtual ~MaitaComponent() = default;

	MaitaComponent(const MaitaComponent& other) = delete;
	MaitaComponent(MaitaComponent&& other) = delete;
	MaitaComponent& operator=(const MaitaComponent& other) = delete;
	MaitaComponent& operator=(MaitaComponent&& other) = delete;

	void Initialize() override;
	void Update() override;

private:
	float m_RockThrowingTimer{};
};
