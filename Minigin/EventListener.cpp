#include "EventListener.h"

using namespace dae;

int EventListener::s_IdCounter{ 0 };

EventListener::EventListener()
{
	m_ID = s_IdCounter;
	++s_IdCounter;
}