#pragma once
#include "Component.h"

namespace dae
{
	class TextObject;

	class FPSCounter final : public Component
	{
	public:
		FPSCounter();
		virtual ~FPSCounter();

		FPSCounter(const FPSCounter& other) = delete;
		FPSCounter(FPSCounter&& other) = delete;
		FPSCounter& operator=(const FPSCounter& other) = delete;
		FPSCounter& operator=(FPSCounter&& other) = delete;

		virtual void Render() override;
		virtual void Update() override;
	private:
		TextObject* m_pText{};
		int m_AmountOfPassedFrames{};
		float m_AccuSec{};
		const float m_UpdateInterval{ 1.f };
	};
}


