#include "HealthComponent.h"

#include "GameObject.h"

#include "TextComponent.h"


void HealthComponent::SetMaxHealth(int newMaxHealth)
{
	m_MaxHealth = newMaxHealth;
	SetHealth(m_MaxHealth);
}

void HealthComponent::SetHealth(int newHealth)
{
	m_CurrHealth = newHealth;
}

int HealthComponent::GetHealth() const
{
	return m_CurrHealth;
}

void HealthComponent::DoDamage(int amount)
{
	//update HP
	m_CurrHealth -= amount;

	//if dies
	if (m_CurrHealth <= 0)
	{
		//Destroy
		m_pOwner->Destroy();
	}
}