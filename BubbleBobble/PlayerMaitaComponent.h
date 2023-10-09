#pragma once
#include <glm/vec2.hpp>

#include "FoodComponent.h"
#include "Subject.h"
#include "SpriteDataPreset.h"

class PlayerMaitaComponent final : public dae::Component
{
public:
	enum class PlayerMaitaState
	{
		Moving,
		Hit
	};

	PlayerMaitaComponent() = default;
	~PlayerMaitaComponent() override = default;

	PlayerMaitaComponent(const PlayerMaitaComponent& other) = delete;
	PlayerMaitaComponent(PlayerMaitaComponent&& other) = delete;
	PlayerMaitaComponent& operator=(const PlayerMaitaComponent& other) = delete;
	PlayerMaitaComponent& operator=(PlayerMaitaComponent&& other) = delete;

	void Initialize() override;
	void Update() override;

	void ThrowRock();

	PlayerMaitaState GetCurrState() const;

	dae::Subject<int> m_HealthChange;

	virtual rapidjson::Value Serialize(rapidjson::Document::AllocatorType&) const override;
	virtual void Deserialize(const rapidjson::Value&) override;

private:
	void UpdateAnimVariablesMoving();
	void DoRespawnLogic();

	PlayerMaitaState m_CurrentState{ PlayerMaitaState::Moving };

	glm::vec2 m_LastPos{};

	float m_Timer{};

	float m_MaxRespawmTimer{ 3.f };

	//using a bool for this state since it can be active in multiple states
	bool m_Invulnerable{};
	float m_MaxInvulnerableTime{ 3.f };

	bool m_Throwing{};
	float m_RockThrowingTimer{};


	static float m_SpriteScale;
	static dae::SpriteDataPreset m_Damaged;
	static dae::SpriteDataPreset m_Walking;
	static dae::SpriteDataPreset m_ThrowBoulder;
};


