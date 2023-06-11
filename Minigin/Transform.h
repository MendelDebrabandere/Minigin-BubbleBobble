#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform final : public Component
	{
	public:
		Transform() = default;
		~Transform() override = default;

		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		const glm::vec2& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec2& GetWorldPosition();
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec2& position);
		void SetWorldPosition(float x, float y);
		void SetWorldPosition(const glm::vec2& position);
		void Translate(float x, float y);
		void Translate(glm::vec2 vec);

		bool GetFacingRight() const;
	private:
		void EnableChangedFlag();
		void UpdateWorldPosition();

		glm::vec2 m_LocalPosition{};
		glm::vec2 m_WorldPosition{};

		bool m_FacingRight{true};

		bool m_HasChanged{};
	};
}
