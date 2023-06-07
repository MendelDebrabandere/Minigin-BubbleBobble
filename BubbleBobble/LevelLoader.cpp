#include "LevelLoader.h"

#include <string>
#include <fstream>

#include "Avatar.h"
#include "AvatarComponent.h"
#include "Block.h"
#include "FPSCounter.h"
#include "Maita.h"
#include "TextComponent.h"
#include "Platform.h"
#include "ResourceManager.h"
#include "ZenChan.h"

using namespace dae;

void LevelLoader::LoadLevel(Scene* pScene, int number, bool loadAvatar)
{
	// load level from file
	std::string line;
	std::string fileName{ "../Data/Level" };
	fileName += std::to_string(number);
	fileName += ".txt";
	std::ifstream myfile(fileName);

	int posX{};
	int posY{};

	constexpr int blockSize{ 32 };

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			for (char letter : line)
			{
				glm::vec2 spawnPos{ blockSize * posX, blockSize * posY };

				switch(letter)
				{
				case '1':
				{
					Block::CreateBlock(pScene, spawnPos, number);
					break;
				}
				case '2':
				{
					Platform::CreatePlatform(pScene, spawnPos, number);
					break;
				}
				case '3':
				{
					Maita::CreateMaita(pScene, spawnPos);
					break;
				}
				case '4':
				{
					ZenChan::CreateZenChan(pScene, spawnPos);
					break;
				}
				case '5':
				{
					if (loadAvatar) 
						Avatar::CreateAvatar(pScene, spawnPos);
					else
					{
						//translate the current one to the pos
						for (auto& go : pScene->GetAllObjects())
						{
							if (go->GetComponent<AvatarComponent>())
							{
								go->GetTransform()->SetWorldPosition(glm::vec2{ blockSize * posX, blockSize * posY });
							}
						}
					}
					break;
				}
				}

				++posX;
			}
			++posY;
			posX = 0;
		}
		myfile.close();
	}

	// FPS COUNTER
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	const auto pFPSCounter = pScene->CreateGameObject();
	pFPSCounter->AddComponent<TextureComponent>();
	pFPSCounter->AddComponent<FPSCounter>();
	pFPSCounter->AddComponent<TextComponent>()->SetFont(pFont);
}
