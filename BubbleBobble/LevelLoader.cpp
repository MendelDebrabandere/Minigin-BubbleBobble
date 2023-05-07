#include "LevelLoader.h"

#include <string>
#include <fstream>

#include "Avatar.h"
#include "Block.h"

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
					Block::CreateBlock(pScene, glm::vec2{ blockSize * posX, blockSize * posY });
					break;
				}
				case '2':
				{
					//TODO: Spawn a Maita
					break;
				}
				case '3':
				{
					//TODO: Spawn a Zen-Chan
					break;
				}
				case '4':
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