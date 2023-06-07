#pragma once
#include "Component.h"

namespace dae
{
	struct CollisionState
	{
		bool BottomCollision{};
		bool TopCollision{};
		bool RightCollision{};
		bool LeftCollision{};
	};

	class PhysicsComponent final : public dae::Component
	{
	public:
		PhysicsComponent() = default;
		virtual ~PhysicsComponent() override = default;
		PhysicsComponent(const PhysicsComponent& other) = delete;
		PhysicsComponent operator=(const PhysicsComponent& rhs) = delete;
		PhysicsComponent(PhysicsComponent&& other) = delete;
		PhysicsComponent operator=(PhysicsComponent&& rhs) = delete;

		void FixedUpdate() override;

		void SetPhysicsSettings(bool gravity, bool collision, bool isStatic);
		void Jump(float speed);
		void SetPlatform(bool val) { m_Platform = val; }

		CollisionState GetCollisionState() const { return m_CollisionState; }
		void SetGrounded(bool val); // used for artificially enabling jump (jumping on bubbles)

	private:

		void DoCollisionLogic();
		void DoGravityLogic();

		bool m_Gravity{ true };
		bool m_Collision{ true };
		bool m_Static{ false };

		CollisionState m_CollisionState{};

		float m_VerticalSpeed{};
		float m_GravityAccel{ 500 };
		float m_MaxFallSpeed{ 1000 };

		bool m_Platform{ false };
	};
}

