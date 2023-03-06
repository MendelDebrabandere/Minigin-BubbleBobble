#pragma once

#include "Component.h"

namespace dae
{
	class RotatorComponent : public Component
	{
	public:
		RotatorComponent() = default;
		virtual ~RotatorComponent() = default;

		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		void SetRotateSpeed(float speed) { m_RotateSpeed = speed; };

		virtual void Update() override;
	private:
		const float m_DistanceFromPivot{ 40.0f };
		float m_RotateSpeed{ 180.0f };
		float m_CurAngle{};
	};
}
