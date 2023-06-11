#pragma once
#include <memory>
#include <SDL_pixels.h>
#include <string>
#include "Component.h"
#include "Font.h"
#include "TextureComponent.h"

namespace dae
{
	class TextComponent final : public Component
	{
	public:
		TextComponent() = default;
		~TextComponent() override = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void SetFont(std::shared_ptr<Font> pFont);
		void SetText(const std::string& text);
		void SetColor(unsigned char r, unsigned char g, unsigned char b);

		void Update() override;


	private:
		void ReloadTexture();

		std::string m_Text{ " " };
		std::shared_ptr<Font> m_pFont{};
		SDL_Color m_Color{ 255,255,255,255 };

		bool m_HasChanged{};

		TextureComponent* m_pTextureRenderer{};
	};

}
