#include "Subject.h"

using namespace dae;

void Subject::UpdateCleanup()
{
	m_Observers.erase(std::remove_if(begin(m_Observers), end(m_Observers), [](const auto& pObserver)
		{
			return pObserver->IsMarkedDead();
		}), end(m_Observers));
}

void Subject::Notify(const GameObject* actor, Observer::Event event)
{
	for (const auto& pObserver : m_Observers)
	{
		pObserver->Notify(actor, event);
	}
}
