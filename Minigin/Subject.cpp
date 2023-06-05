#include "Subject.h"

using namespace dae;

template<typename... Args>
Subject<Args...>::~Subject()
{
	for (auto& observer : m_ObserverPtrs)
	{
		observer->OnSubjectDestroy();
	}
}

template<typename ...Args>
void Subject<Args...>::AddObserver(Observer<Args...>* pObserver)
{
	m_ObserverPtrs.push_back(pObserver);
}

template<typename ...Args>
void Subject<Args...>::RemoveObserver(Observer<Args...>* pObserver)
{
	m_ObserverPtrs.erase(std::remove(
		m_ObserverPtrs.begin(),
		m_ObserverPtrs.end(), pObserver),
		m_ObserverPtrs.end());
}

template<typename ...Args>
void dae::Subject<Args...>::Notify(Args ...args)
{
	for (auto& pObserver : m_ObserverPtrs)
	{
		pObserver->HandleEvent(args...);
	}
}
