#include "TextureComponent.h"

#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "Transform.h"

using namespace dae;

void TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	m_pTexture = pTexture;
}

void TextureComponent::Render() const
{
	// If no texture has been assigned to this TextureComponent, do nothing
	if (!m_pTexture) return;

	// Render the current texture at the position defined by the transform
	const glm::vec2 pos = m_pOwner->GetTransform()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

glm::vec2 TextureComponent::GetTextureSize()
{
	return m_pTexture->GetSize();
}
