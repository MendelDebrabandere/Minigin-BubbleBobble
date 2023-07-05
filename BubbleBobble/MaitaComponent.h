#pragma once
#include "Component.h"
#include "SpriteComponent.h"

class MaitaComponent final : public dae::Component
{
public:
	MaitaComponent();
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

	static float m_SpriteScale;
	static dae::SpriteDataPreset m_WalkingPreset;
	static dae::SpriteDataPreset m_AttackingPreset;
};
