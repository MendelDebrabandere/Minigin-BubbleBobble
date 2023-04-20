#pragma once
#include <vector>
#include "Observer.h"

namespace dae
{
	class GameObject;

	class Subject final
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(const GameObject* actor, int eventID);

	private:
		std::vector<Observer*> m_observers;
	};

}

