#include "TextureComponent.h"
#include <glm/vec2.hpp>
#include "Renderer.h"
#include "Transform.h"

void dae::TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	m_pTexture = pTexture;
}

void dae::TextureComponent::Render() const
{
	// If no texture has been assigned to this TextureComponent, do nothing
	if (!m_pTexture) return;

	// Render the current texture at the position defined by the transform
	const glm::vec2& pos = GetTransform()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}