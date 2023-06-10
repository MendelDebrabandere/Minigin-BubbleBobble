#pragma once

#include "Singleton.h"

#include "Event.h"
#include "EventListener.h"

#include <queue>

namespace dae
{
	class EventQueue final : public Singleton<EventQueue>
	{
	public:

		//add event to queue
		void SendEvent(const Event& event);

		//once every frame do all the events
		void NotifyListeners();

		void AddListener(EventListener* listener);
		void RemoveListener(int listenerId);



	private:
		bool PollEvent(Event& e);

		std::queue<Event> m_EventQueue{};

		
		std::vector<EventListener*> m_Listeners;
	};
}

