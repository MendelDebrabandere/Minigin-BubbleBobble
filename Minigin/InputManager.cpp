#include <SDL.h>
#include "InputManager.h"

using namespace dae;

bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	for (auto& controller: m_ControllerPtrs)
	{
		controller->Update();

		for (auto& mapPair: m_ActionMap)
		{
			if (mapPair.first.first == controller->GetIdx())
			{
				if (controller->IsPressed(mapPair.first.second) || 
					(mapPair.first.second == XBox360Controller::ControllerButton::LeftThumbStick)) // thumbstick actions should always be allowed
				{
					mapPair.second->Execute(mapPair.first.first);
				}
			}
		}
	}

	return true;
}

XBox360Controller* InputManager::GetController(unsigned int controllerIdx)
{
	for (auto& controller: m_ControllerPtrs)
	{
		if (controller->GetIdx() == controllerIdx)
		{
			return controller.get();
		}
	}
	return nullptr;
}


