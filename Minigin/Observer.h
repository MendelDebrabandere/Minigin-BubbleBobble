#pragma once

namespace dae
{
	class GameObject;

	class Observer
	{
	public:
		enum class Event
		{
			ActorDied,
			HealthUpdated,
			ScoreUpdated
		};

		Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void Notify(const GameObject* actor, Event event) = 0;

		void Destroy() { m_MarkedDead = true; }
		bool IsMarkedDead() const { return m_MarkedDead; }

	protected:
		bool m_MarkedDead{};
	};
}