#pragma once
#include "Component.h"
#include "SpriteDataPreset.h"

class RockComponent final : public dae::Component
{
public:
	RockComponent() = default;
	~RockComponent() override = default;

	RockComponent(const RockComponent& other) = delete;
	RockComponent(RockComponent&& other) = delete;
	RockComponent& operator=(const RockComponent& other) = delete;
	RockComponent& operator=(RockComponent&& other) = delete;

	void Initialize() override;
	void Update() override;

	void SetMoveRight(bool right);
	void Crash();

	bool CanDamage() const;

	virtual rapidjson::Value Serialize(rapidjson::Document::AllocatorType&) const override;
	virtual void Deserialize(const rapidjson::Value&) override;

private:
	enum class RockState
	{
		Rolling,
		Crashing
	};

	RockState m_CurrState{};

	float m_HorMoveSpeed{};
	bool m_MoveRight{};

	float m_CrashingTimer{};

	static float m_SpriteScale;
	static dae::SpriteDataPreset m_CrashAnim;
};
