#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;
}

class FPSCounter final : public dae::Component
{
public:
	FPSCounter() = default;
	virtual ~FPSCounter() = default;

	FPSCounter(const FPSCounter& other) = delete;
	FPSCounter(FPSCounter&& other) = delete;
	FPSCounter& operator=(const FPSCounter& other) = delete;
	FPSCounter& operator=(FPSCounter&& other) = delete;

	virtual void Update() override;
private:
	int m_AmountOfPassedFrames{};
	float m_AccuSec{};
	const float m_UpdateInterval{ 1.f };
	int m_FPS{};

	dae::TextComponent* m_pText{};
};

