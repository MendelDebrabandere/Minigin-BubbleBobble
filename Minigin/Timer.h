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
		float GetTotal() const { return m_TotalTime; }
	private:
		std::chrono::steady_clock::time_point m_StartTime{};
		std::chrono::steady_clock::time_point m_LastTime{};

		float m_DeltaTime{};

		float m_TotalTime{};
	};
}

