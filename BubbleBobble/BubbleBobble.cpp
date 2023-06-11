#include "BubbleBobble.h"

#include <ctime>
#include <iostream>

#include "NullSoundSystem.h"
#include "ResourceManager.h"
#include "SceneSwapper.h"
#include "ServiceLocator.h"

using namespace dae;

void BubbleBobble::Create()
{
	// Seed rand() with current time
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//ServiceLocator::RegisterSoundSystem(new NullSoundSystem());

	SceneSwapper::GetInstance().Init();

	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "WASD and spacebar are the controls for keybard\n";
	std::cout << "DPAD and A and B are the controls for controller\n";
	std::cout << "\n";
	std::cout << "F1 to skip a level\n";
	std::cout << "F2 to toggle audio mute\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";

}

