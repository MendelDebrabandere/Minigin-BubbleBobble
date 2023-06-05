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
		size_t previousSize = m_KeyboardActionMap.size();
		for (auto& mapPair : m_KeyboardActionMap)
		{
			if (unsigned int(e.key.keysym.sym) == mapPair.first.key)
			{
				//DOWN
				if (mapPair.first.type == InputType::OnDown && e.type == SDL_KEYDOWN)
				{
					//Check if it isnt being held down
					if (std::ranges::find(m_PressedKeys, mapPair.first.key) != m_PressedKeys.end())
						continue;

					mapPair.second->Execute();
				}

				//RELEASE
				else if (mapPair.first.type == InputType::OnRelease && e.type == SDL_KEYUP)
					mapPair.second->Execute();

				//if a command changed the input map
				if (m_KeyboardActionMap.size() != previousSize)
				{
					//stop the loop
					break;
				}
			}
		}
	}

	m_PressedKeys.clear();

	//Keyboard Pressed continuously
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	for (auto& mapPair : m_KeyboardActionMap)
	{
		if (state[SDL_GetScancodeFromKey(mapPair.first.key)])
		{
			m_PressedKeys.push_back(mapPair.first.key);

			if (mapPair.first.type == InputType::Pressed)
			{
				mapPair.second->Execute();
			}
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
	m_ControllerActionMap.insert(std::pair(inputData, std::move(pCommand)));
}

void InputManager::AddKeyboardCommand(unsigned int keyboardKey, InputType type, std::unique_ptr<Command> pCommand)
{
	//make the action and add it to the map
	InputDataKeyboard inputData{ keyboardKey, type };
	m_KeyboardActionMap.insert(std::pair(inputData, std::move(pCommand)));
}

bool InputManager::IsKeyboardKeyDown(unsigned int keyboardKey)
{
	return std::ranges::find(m_PressedKeys, keyboardKey) != m_PressedKeys.end();
}

void InputManager::RemoveAllInputs()
{
	m_KeyboardActionMap.clear();
	m_ControllerActionMap.clear();
}
