#pragma once
#include "Component.h"
#include "SpriteDataPreset.h"

class ZenChanComponent final : public dae::Component
{
public:
	ZenChanComponent();
	~ZenChanComponent() override = default;

	ZenChanComponent(const ZenChanComponent& other) = delete;
	ZenChanComponent(ZenChanComponent&& other) = delete;
	ZenChanComponent& operator=(const ZenChanComponent& other) = delete;
	ZenChanComponent& operator=(ZenChanComponent&& other) = delete;

	void Initialize() override;
	void Update() override;

	virtual rapidjson::Value Serialize(rapidjson::Document::AllocatorType&) const override;
	virtual void Deserialize(const rapidjson::Value&) override;

private:
	bool m_Charging{};
	float m_ChargingTimer{};

	static float m_SpriteScale;
	static dae::SpriteDataPreset m_WalkingPreset;
	static dae::SpriteDataPreset m_ChargingPreset;
};
