#pragma once
#include "Event.h"

namespace dae
{
	class EventListener
	{
	public:
		EventListener();
		virtual ~EventListener() = default;
		EventListener(const EventListener&) = delete;
		EventListener(EventListener&&) = delete;
		EventListener& operator= (const EventListener&) = delete;
		EventListener& operator= (const EventListener&&) = delete;

		virtual void OnEvent(const Event& event) = 0;

		int GetId() const { return m_ID; }

	private:
		int m_ID{};

		static int s_IdCounter;
	};
}
