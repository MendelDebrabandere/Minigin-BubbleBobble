#pragma once
#include <vector>

#include "Observer.h"

namespace dae
{
	template<typename... Args>
	class Subject final
	{
	public:
		~Subject();

		void AddObserver(Observer<Args...>* pObserver);

		void RemoveObserver(Observer<Args...>* pObserver);

		void Notify(Args... args);

	private:
		std::vector<Observer<Args ...>*> m_ObserverPtrs;
	};
}

