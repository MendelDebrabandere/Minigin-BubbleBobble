#include "EventListener.h"

#include "EventQueue.h"

using namespace dae;

EventListener::EventListener()
{
	EventQueue::GetInstance().AddListener(this);
}

EventListener::~EventListener()
{
	EventQueue::GetInstance().RemoveListener(this);
}
