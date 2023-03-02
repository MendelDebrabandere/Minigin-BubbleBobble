#pragma once
#include <chrono>
#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		void Init();
		void Update();

		float GetDelta() const { return m_DeltaTime; }
	private:
		std::chrono::steady_clock::time_point m_LastTime{};
		float m_DeltaTime{};
	};
}

