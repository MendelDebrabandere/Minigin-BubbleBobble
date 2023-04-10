#include "Subject.h"

using namespace dae;

void Subject::RemoveObeserver(Observer* observer)
{
	m_Observers.erase(std::remove_if(begin(m_Observers), end(m_Observers), [observer](const auto& uniqueObserver)
		{
			return uniqueObserver.get() == observer;
		}), end(m_Observers));
}

void Subject::Notify(const GameObject* actor, Observer::Event event)
{
	for (const auto& pObserver : m_Observers)
	{
		pObserver->Notify(actor, event);
	}
}
