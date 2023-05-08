#pragma once
#include "Component.h"

namespace dae
{
	class PhysicsComponent final : public dae::Component
	{
	public:
		PhysicsComponent() = default;
		virtual ~PhysicsComponent() override = default;
		PhysicsComponent(const PhysicsComponent& other) = delete;
		PhysicsComponent operator=(const PhysicsComponent& rhs) = delete;
		PhysicsComponent(PhysicsComponent&& other) = delete;
		PhysicsComponent operator=(PhysicsComponent&& rhs) = delete;

		void Update() override;

		void SetPhysicsSettings(bool gravity, bool collision, bool isStatic);

		bool GetCollision() const { return m_Collision; }

	private:
		void DoCollisionLogic();
		void DoGravityLogic();

		bool m_Gravity{ true };
		bool m_Collision{ true };
		bool m_Static{ false };

		bool m_IsGrounded{ false };
	};
}

