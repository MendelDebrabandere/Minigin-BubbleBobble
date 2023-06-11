#pragma once
#include <functional>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

#include "Component.h"

namespace dae
{
	class ColliderComponent final : public Component
	{
	public:
		enum class OverlapData
		{
			Bottom,
			Top,
			Left,
			Right,
			Not
		};

		ColliderComponent() = default;
		~ColliderComponent() override = default;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent operator=(const ColliderComponent& rhs) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent operator=(ColliderComponent&& rhs) = delete;

		void FixedUpdate() override;
		void Render() const override;

		void SetRendering(bool value) { m_DrawDebug = value; }
		bool IsOverlappingWith(const ColliderComponent* other);
		std::pair<OverlapData, float> IsOverlappingWithDirectional(const ColliderComponent* other);

		void SetSize(const glm::vec2& val);
		void UpdatePos();

		const glm::vec2& GetSize() const { return m_Size; }
		const glm::vec2& GetPos() const { return m_Pos; }

		void SetOverlapFunction(std::function<void(GameObject*)> overlapFunction);

	private:
		void CheckForOverlaps();

		glm::vec2 m_Pos{};
		glm::vec2 m_Size{};

		bool m_DrawDebug{ false };
		glm::vec4 m_Color{ 255,0,0,255 };

		std::function<void(GameObject*)> m_OverlapFunction;
	};
}

