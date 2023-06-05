#include "LevelLoader.h"

#include <string>
#include <fstream>

#include "Avatar.h"
#include "Block.h"
#include "Platform.h"
#include "ZenChan.h"

using namespace dae;

void LevelLoader::LoadLevel(Scene* pScene, int number)
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
				switch(letter)
				{
				case '1':
				{
					Block::CreateBlock(pScene, glm::vec2{ blockSize * posX, blockSize * posY }, number);
					break;
				}
				case '2':
				{
					Platform::CreatePlatform(pScene, glm::vec2{ blockSize * posX, blockSize * posY }, number);
					break;
				}
				case '3':
				{
					//TODO: Spawn a Maita
					break;
				}
				case '4':
				{
					ZenChan::CreateZenChan(pScene, glm::vec2{ blockSize * posX, blockSize * posY });
					break;
				}
				case '5':
				{
					Avatar::CreateAvatar(pScene, glm::vec2{ blockSize * posX, blockSize * posY });
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
}
