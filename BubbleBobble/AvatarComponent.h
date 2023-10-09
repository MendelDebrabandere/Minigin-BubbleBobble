#pragma once
#include <glm/vec2.hpp>

#include "FoodComponent.h"
#include "Subject.h"
#include "SpriteDataPreset.h"

class AvatarComponent final : public dae::Component
{
public:
	enum class AvatarState
	{
		Moving,
		Hit
	};

	enum class AvatarColor
	{
		green,
		blue
	};

	AvatarComponent() = default;
	~AvatarComponent() override = default;

	AvatarComponent(const AvatarComponent& other) = delete;
	AvatarComponent(AvatarComponent&& other) = delete;
	AvatarComponent& operator=(const AvatarComponent& other) = delete;
	AvatarComponent& operator=(AvatarComponent&& other) = delete;

	void Initialize() override;
	void Update() override;

	AvatarState GetCurrState() const;

	void SetColor(AvatarColor color);
	AvatarColor GetColor() const;

	void PickedUpFood(FoodComponent::FoodType type);

	dae::Subject<FoodComponent::FoodType> m_FoodPickup;
	dae::Subject<int> m_HealthChange;


	virtual rapidjson::Value Serialize(rapidjson::Document::AllocatorType&) const override;
	virtual void Deserialize(const rapidjson::Value&) override;

private:
	void UpdateAnimVariablesMoving();
	void DoRespawnLogic();

	AvatarState m_CurrentState{ AvatarState::Moving };

	glm::vec2 m_LastPos{};

	float m_Timer{};

	float m_MaxRespawmTimer{ 3.f };

	//using a bool for this state since it can be active in multiple states
	bool m_Invulnerable{};
	float m_MaxInvulnerableTime{3.f};

	AvatarColor m_MyColor{};

	static float m_SpriteScale;
	static dae::SpriteDataPreset m_GreenWalking;
	static dae::SpriteDataPreset m_GreenDamaged;
	static dae::SpriteDataPreset m_BlueWalking;
	static dae::SpriteDataPreset m_BlueDamaged;
};
