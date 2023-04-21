#include "Hero.h"

using namespace dae;

void Hero::TakeDamage(int amount)
{
	m_health -= amount;
	healthChanged.Notify();
}

void Hero::PickupLoot(LootType type)
{
	// add code to add the loot to
	// an inventory or something
	foundLoot.Notify(type);
}
