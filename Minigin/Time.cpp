#include "Time.h"

void dae::Time::Init()
{
	// setup m_LastTime
	m_LastTime = std::chrono::high_resolution_clock::now();
}

void dae::Time::SetFixedTimeStep(float fixedTimeStep)
{
	m_FixedTimeStep = fixedTimeStep;
}

void dae::Time::Update()
{
	// Get the current time
	const auto currTime{ std::chrono::high_resolution_clock::now() };

	// Update m_DeltaTime
	m_DeltaTime = std::chrono::duration<float>(currTime - m_LastTime).count();

	// Store the time for next frame
	m_LastTime = currTime;
}