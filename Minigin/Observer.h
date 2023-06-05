#pragma once

namespace dae
{
	template<typename... Args>
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator=(const Observer&) = delete;
		Observer& operator=(Observer&&) = delete;

		virtual void HandleEvent(Args... args) = 0;
		virtual void OnSubjectDestroy() = 0;
	};
}