#pragma once
#include <vector>
#include "Observer.h"

namespace dae
{
	class GameObject;

	template<typename... Args>
	class Subject final
	{
	public:
		~Subject()
		{
			for (auto& observer : m_observers)
				observer->OnSubjectDestroy();
		}
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

		void AddObserver(Observer<Args...>* observer)
		{
			m_observers.push_back(observer);
		}

		void RemoveObserver(Observer<Args...>* observer)
		{
			m_observers.erase(std::remove(
				m_observers.begin(),
				m_observers.end(), observer),
				m_observers.end());
		}

		void Notify(Args... args)
		{
			for (auto& observer : m_observers)
				observer->HandleEvent(args...);
		}

	private:
		std::vector<Observer<Args...>*> m_observers;
	};

}

