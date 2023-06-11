#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureComponent final : public Component
	{
	public:
		TextureComponent() = default;
		~TextureComponent() override = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void SetTexture(const std::shared_ptr<Texture2D>& pTexture);

		void Render() const override;

		glm::vec2 GetTextureSize() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};

	};
}
