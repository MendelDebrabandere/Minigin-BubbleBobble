#include "Subject.h"

void dae::Subject::AddObserver(Observer* observer)
{
		m_observers.push_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	m_observers.erase(std::remove(
		m_observers.begin(),
		m_observers.end(), observer),
		m_observers.end());
}

void dae::Subject::Notify(const GameObject* actor, int eventID)
{
	for (auto& observer : m_observers)
		observer->Notify(actor, eventID);
}
