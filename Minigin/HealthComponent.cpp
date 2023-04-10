#include "HealthComponent.h"

#include <iostream>

#include "GameObject.h"
#include <sstream>

#include "Subject.h"
#include "TextComponent.h"
#include "Time.h"

using namespace dae;

void HealthComponent::Update()
{
	std::cout << Time::GetInstance().GetTotal() << '\n';
	if (Time::GetInstance().GetTotal() >= 5.f)
	{
		DoDamage(1);
	}
}

void HealthComponent::SetMaxHealth(int newMaxHealth)
{
	m_MaxHealth = newMaxHealth;
	SetHealth(m_MaxHealth);
}

void HealthComponent::SetHealth(int newHealth)
{
	m_CurrHealth = newHealth;
	Subject::GetInstance().Notify(m_pOwner, Observer::Event::HealthUpdated);
}

int HealthComponent::GetHealth() const
{
	return m_CurrHealth;
}

void HealthComponent::DoDamage(int amount)
{
	//update HP
	m_CurrHealth -= amount;
	Subject::GetInstance().Notify(m_pOwner, Observer::Event::HealthUpdated);

	//if dies
	if (m_CurrHealth <= 0)
	{
		//Destroy
		m_pOwner->Destroy();
		Subject::GetInstance().Notify(m_pOwner, Observer::Event::ActorDied);
	}
}