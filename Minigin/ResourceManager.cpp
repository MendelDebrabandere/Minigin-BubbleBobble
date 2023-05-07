#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

using namespace dae;

void ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

void ResourceManager::CheckForDeletedTextures()
{
	std::string deleteStr{};
	for (const auto& pair: m_Textures)
	{
		if (pair.second.use_count() <= 1)
		{
			deleteStr = pair.first;
			break;
		}
	}
	if (!deleteStr.empty())
		m_Textures.erase(deleteStr);

	deleteStr = std::string();
	for (const auto& pair : m_Fonts)
	{
		if (pair.second.use_count() <= 1)
		{
			deleteStr = pair.first;
			break;
		}
	}
	if (!deleteStr.empty())
		m_Fonts.erase(deleteStr);

}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file)
{
	if (m_Textures.contains(file))
	{
		return m_Textures[file];
	}
	
	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	m_Textures[file] = std::make_shared<Texture2D>(texture);

	return m_Textures[file];
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	if (m_Fonts.contains(file))
	{
		return m_Fonts[file];
	}

	m_Fonts[file] = std::make_shared<Font>(m_dataPath + file, size);

	return m_Fonts[file];
}
