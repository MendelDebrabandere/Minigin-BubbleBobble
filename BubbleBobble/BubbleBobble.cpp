#include "BubbleBobble.h"

#include <random>
#include <ctime>
#include <iostream>

#include "FPSCounter.h"
#include "InputManager.h"
#include "LeaveMenuCommand.h"
#include "LevelLoader.h"
#include "NullSoundSystem.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SceneSwapper.h"
#include "ServiceLocator.h"
#include "TextComponent.h"

using namespace dae;

void BubbleBobble::Create()
{
	// Seed rand() with current time
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	ServiceLocator::RegisterSoundSystem(new NullSoundSystem());

	SceneSwapper::GetInstance().Init();

	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "WASD and spacebar are the current controls\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";

}

