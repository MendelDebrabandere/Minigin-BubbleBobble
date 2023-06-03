#pragma once
#include <SDL_rect.h>
#include <string>
#include <glm/vec2.hpp>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class SpriteComponent final : public Component
	{
	public:
		SpriteComponent();
		virtual ~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Update() override;
		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetAnimVariables(int rows, int columns, float animTimer, int startIdx=0, int endIdx=0);
		void Scale(float value);
		void Pause(bool value);

		void FlipTexture(bool value);

		glm::vec2 GetSize() const;
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		float m_RenderWidth{};
		float m_RenderHeight{};
		glm::vec2 m_RenderPos{};

		SDL_Rect m_Rect{};
		int m_Rows{};
		int m_Columns{};

		int m_CurrIdx{};
		int m_StartIdx{};
		int m_EndIdx{};

		float m_CurrTime{};
		float m_AnimTimer{};
		bool m_Pause{};

		bool m_FlipTexture{true};
	};
}
