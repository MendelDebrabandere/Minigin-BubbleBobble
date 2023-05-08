#include "Timer.h"

using namespace dae;

void Time::Init()
{
	// setup m_LastTime
	m_LastTime = std::chrono::high_resolution_clock::now();
	m_StartTime = std::chrono::high_resolution_clock::now();
}

void Time::Update()
{
	// Get the current time
	const auto currTime{ std::chrono::high_resolution_clock::now() };

	// Update m_DeltaTime and m_TotalTime
	m_DeltaTime = std::chrono::duration<float>(currTime - m_LastTime).count();
	m_TotalTime = std::chrono::duration<float>(currTime - m_StartTime).count();

	// Store the time for next frame
	m_LastTime = currTime;
}

void Time::SetFixedTimeStep(float fixedTimeStep)
{
	m_FixedTimeStep = fixedTimeStep;
}
