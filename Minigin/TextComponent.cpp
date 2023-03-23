#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include "Texture2D.h"

void dae::TextComponent::SetFont(std::shared_ptr<Font> pFont)
{
	m_pFont = pFont;
	m_HasChanged = true;
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_HasChanged = true;
}

void dae::TextComponent::Update()
{
	if (!m_HasChanged) return;

	ReloadTexture();

	m_HasChanged = false;
}

void dae::TextComponent::ReloadTexture()
{
	if (!m_pFont) return;

	if (m_pTextureRenderer.expired())
	{
		m_pTextureRenderer = GetOwner()->GetComponent<TextureComponent>();

		if (m_pTextureRenderer.expired()) return;
	};

	// Create a texture using the current font, text and color
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), SDL_Color{ 255,255,255 });
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	const auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);

	// Set the new texture to the texture renderer
	m_pTextureRenderer.lock()->SetTexture(std::make_shared<Texture2D>(texture));
}