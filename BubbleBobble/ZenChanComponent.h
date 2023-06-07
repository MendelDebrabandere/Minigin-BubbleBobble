#pragma once
#include "Component.h"

class ZenChanComponent : public dae::Component
{
public:
	ZenChanComponent() = default;
	virtual ~ZenChanComponent() = default;

	ZenChanComponent(const ZenChanComponent& other) = delete;
	ZenChanComponent(ZenChanComponent&& other) = delete;
	ZenChanComponent& operator=(const ZenChanComponent& other) = delete;
	ZenChanComponent& operator=(ZenChanComponent&& other) = delete;

	void Update() override;

private:
	bool m_Charging{};
	float m_ChargingTimer{ float(rand() % 20 + 10) };
};
