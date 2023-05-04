#pragma once

namespace dae
{
	class Observer
	{
	public:
		explicit Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator=(const Observer&) = delete;
		Observer& operator=(Observer&&) = delete;

		virtual void OnNotify(size_t subject, int event, int value) = 0;
	};
}