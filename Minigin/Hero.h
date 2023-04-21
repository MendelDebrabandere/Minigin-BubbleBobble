#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	enum class LootType
	{
		Pellet,
		SuperPellet
	};


	class Hero final : public Component
	{
	public:
		Hero(GameObject* owner, int health);
		virtual ~Hero() = default;
		Hero(const Hero& other) = delete;
		Hero& operator=(const Hero& other) = delete;
		Hero(Hero&& other) = delete;
		Hero& operator=(Hero&& other) = delete;

		int GetHealth() const { return m_health; }

		void TakeDamage(int amount);
		void PickupLoot(LootType type);

		Subject<> healthChanged;
		Subject<LootType> foundLoot;

	private:
		int m_health;
	};
}

