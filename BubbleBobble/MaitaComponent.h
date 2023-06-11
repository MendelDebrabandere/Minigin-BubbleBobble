#pragma once
#include "Component.h"

class MaitaComponent final : public dae::Component
{
public:
	MaitaComponent() = default;
	~MaitaComponent() override = default;

	MaitaComponent(const MaitaComponent& other) = delete;
	MaitaComponent(MaitaComponent&& other) = delete;
	MaitaComponent& operator=(const MaitaComponent& other) = delete;
	MaitaComponent& operator=(MaitaComponent&& other) = delete;

	void Initialize() override;
	void Update() override;

private:
	bool m_Throwing{};
	float m_RockThrowingTimer{};
};
