#include "MaitaComponent.h"

void MaitaComponent::Initialize()
{
	m_RockThrowingTimer = float(rand() % 2 + 1);
}

void MaitaComponent::Update()
{
	if (m_RockThrowingTimer < 0.f)
	{
		m_RockThrowingTimer = float(rand() % 2 + 1);

		//TODO: spawn r(c)ock
	}
}