#pragma once
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

#include "Component.h"

namespace dae
{
	class ColliderComponent final : public Component
	{
	public:
		explicit ColliderComponent();
		virtual ~ColliderComponent() override = default;
		ColliderComponent(const Component& other) = delete;
		ColliderComponent operator=(const Component& rhs) = delete;
		ColliderComponent(Component&& other) = delete;
		ColliderComponent operator=(Component&& rhs) = delete;

		void Update() override;
		void Render() const override;

		void SetRendering(bool value) { m_DrawDebug = value; }
		bool IsOverlappingWith(const GameObject& other) const;

		void SetSize(const glm::vec2& val) { m_Size = val; }

		glm::vec2 GetSize() const { return m_Size; }
		glm::vec2 GetPos() const { return m_Pos; }


	private:
		glm::vec2 m_Pos{};
		glm::vec2 m_Size{};

		bool m_DrawDebug{ false };
		glm::vec4 m_Color{ 255,0,0,255 };
	};
}

