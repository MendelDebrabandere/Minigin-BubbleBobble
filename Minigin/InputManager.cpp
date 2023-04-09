#include <SDL.h>
#include "InputManager.h"

using namespace dae;

bool InputManager::ProcessInput()
{
	//Keyboard part
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		//Keyboard OnDown and OnRelease
		for (auto& mapPair : m_KeyboardActionMap)
		{
			if (unsigned int(e.key.keysym.sym) == mapPair.first.key)
			{
				if (mapPair.first.type == InputType::OnDown && e.type == SDL_KEYDOWN)
					mapPair.second->Execute();

				else if (mapPair.first.type == InputType::OnRelease && e.type == SDL_KEYUP)
					mapPair.second->Execute();
			}
		}
	}

	//Keyboard Pressed continuously
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	for (auto& mapPair : m_KeyboardActionMap)
	{
		if (mapPair.first.type == InputType::Pressed)
		{
			if (state[SDL_GetScancodeFromKey(mapPair.first.key)])
				mapPair.second->Execute();
		}
	}



	//Controller part
	for (auto& controller: m_ControllerPtrs)
	{
		controller->Update();

		for (auto& mapPair: m_ControllerActionMap)
		{
			if (mapPair.first.controllerID == controller->GetIdx())
			{
				if (mapPair.first.type == InputType::OnDown && controller->IsDown(mapPair.first.button))
					mapPair.second->Execute();

				else if (mapPair.first.type == InputType::Pressed && controller->IsPressed(mapPair.first.button))
					mapPair.second->Execute();

				else if (mapPair.first.type == InputType::OnRelease && controller->IsUp(mapPair.first.button))
					mapPair.second->Execute();
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


void InputManager::AddControllerCommand(XBox360Controller::ControllerButton button, unsigned int controllerID, InputType type, std::unique_ptr<Command> pCommand)
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
	InputDataController inputData{ controllerID, button, type };
	m_ControllerActionMap[inputData] = std::move(pCommand);
}

void InputManager::AddKeyboardCommand(unsigned int keyboardKey, InputType type, std::unique_ptr<Command> pCommand)
{
	//make the action and add it to the map
	InputDataKeyboard inputData{ keyboardKey, type };
	m_KeyboardActionMap[inputData] = std::move(pCommand);
}