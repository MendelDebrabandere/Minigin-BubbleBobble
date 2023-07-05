#pragma once
#include <memory>
#include <SDL_rect.h>
#include <string>
#include <glm/vec2.hpp>
#include "Texture2D.h"

#include "Component.h"

namespace dae
{
	//This is a preset that can be saved in the class that changes the sprite around
	//So that there is no need to hard code all those values in code and you can store them
	struct SpriteDataPreset
	{
		bool DoOnce;
		int Rows;
		int Columns;
		float AnimTimer;
		int StartIdx;
		int EndIdx;
	};


	class SpriteComponent final : public Component
	{
	public:
		SpriteComponent() = default;
		~SpriteComponent() override = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Update() override;
		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetAnimVariables(int rows, int columns, float animTimer, int startIdx = 0, int endIdx = 0);
		void SetAnimVariables(const SpriteDataPreset& preset);
		void Scale(float value);
		void Pause(bool value);
		void FlipTexture(bool value);
		void DoOnceAnim(float animTimer, int startIdx, int endIdx);
		void ToggleVisuals(bool value);
		bool IsDoingOnce() const;

		glm::vec2 GetSize() const;
		void SetRenderOffset(const glm::vec2& offset);
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

		bool m_FlipTexture{};

		//Do once anim variables
		bool m_DoOnceAnim{};
		int m_DoOnceEndIdx{};
		float m_DoOnceAnimTimer{};

		bool m_Show{ true };

		glm::vec2 m_RenderOffset{};
	};
}
