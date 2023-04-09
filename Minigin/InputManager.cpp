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
		for (auto& mapPair : m_KeyboardActionMap)
		{
			if (mapPair.first == unsigned(e.key.keysym.sym))
			{
				mapPair.second->Execute();
			}
		}
	}

	for (auto& controller: m_ControllerPtrs)
	{
		controller->Update();

		for (auto& mapPair: m_ControllerActionMap)
		{
			if (mapPair.first.first == controller->GetIdx())
			{
				if (controller->IsPressed(mapPair.first.second))
				{
					mapPair.second->Execute();
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


void InputManager::AddControllerCommand(XBox360Controller::ControllerButton button, unsigned int controllerID, std::unique_ptr<Command> pCommand)
{
	//does controller exist yet?
	bool doesControllerExist{ false };
	for (const auto& controller : m_ControllerPtrs)
	{
		if (controller->GetIdx() == controllerID)
		{
			doesControllerExist = true;
			break;
		}
	}

	if (doesControllerExist == false)
	{
		//make new controller
		m_ControllerPtrs.push_back(std::make_unique<XBox360Controller>(controllerID));
	}

	//make the action and add it to the map
	m_ControllerActionMap[std::pair(controllerID, button)] = std::move(pCommand);
}

void InputManager::AddKeyboardCommand(unsigned int keyboardKey, std::unique_ptr<Command> pCommand)
{
	//make the action and add it to the map
	m_KeyboardActionMap[keyboardKey] = std::move(pCommand);
}