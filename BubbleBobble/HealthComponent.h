#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;

	class HealthComponent final : public Component
	{
	public:
		explicit HealthComponent() = default;
		virtual ~HealthComponent() = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		//Setters
		void SetMaxHealth(int newMaxHealth);
		void SetHealth(int newHealth);

		//Getters
		int GetHealth() const;

		void DoDamage(int amount);

	private:
		int m_MaxHealth{100};
		int m_CurrHealth{100};
	};
}

