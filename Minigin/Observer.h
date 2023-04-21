#pragma once

namespace dae
{
	class GameObject;

	template<typename... Args>
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void HandleEvent(Args... args) = 0;
		virtual void OnSubjectDestroy() = 0;
	};
}