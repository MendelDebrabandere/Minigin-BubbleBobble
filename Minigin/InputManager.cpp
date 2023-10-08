#include <SDL.h>
#include "InputManager.h"

#include <iostream>
#include <sstream>
#include "EventQueue.h"
#include "Minigin.h"
#include "ServerConnector.h"

using namespace dae;

bool InputManager::ProcessInput()
{
	ClientInputPacket inputPacket;

	//Keyboard part
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}

		//Keyboard OnDown and OnRelease
		size_t previousSize = m_KeyboardActionMap.size();
		for (auto& mapPair : m_KeyboardActionMap)
		{
			if (static_cast<unsigned int>(e.key.keysym.sym) == mapPair.first.key)
			{
				//DOWN
				if (mapPair.first.type == InputType::OnDown && e.type == SDL_KEYDOWN)
				{
					//Check if it isnt being held down
					if (std::ranges::find(m_PressedKeys, mapPair.first.key) != m_PressedKeys.end())
						continue;

					mapPair.second->Execute();
					inputPacket.pressedKeys.push_back(static_cast<unsigned>(e.key.keysym.sym));
				}

				//RELEASE
				else if (mapPair.first.type == InputType::OnRelease && e.type == SDL_KEYUP)
				{
					mapPair.second->Execute();
					inputPacket.releasedKeys.push_back(static_cast<unsigned>(e.key.keysym.sym));
				}

				//if a command changed the input map
				if (m_KeyboardActionMap.size() != previousSize)
				{
					//stop the loop
					break;
				}
			}
		}

		if (e.type == SDL_KEYDOWN)
		{
			//broadcast event of onkeydown
			if ((e.key.keysym.sym >= 'a' && e.key.keysym.sym <= 'z') || e.key.keysym.sym == SDLK_BACKSPACE)
			{
				//check if the key isnt being held down
				if (std::ranges::find(m_PressedKeys, static_cast<unsigned>(e.key.keysym.sym)) != m_PressedKeys.end())
					continue;

				EventQueue::GetInstance().SendEvent(Event{std::string{char(e.key.keysym.sym)}});
			}
		}
	}

	m_PressedKeys.clear();

	//Keyboard Pressed continuously
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	for (auto& mapPair : m_KeyboardActionMap)
	{
		if (state[SDL_GetScancodeFromKey(static_cast<int>(mapPair.first.key))])
		{
			m_PressedKeys.push_back(mapPair.first.key);

			if (mapPair.first.type == InputType::Pressed)
			{
				mapPair.second->Execute();
				inputPacket.heldKeys.push_back(mapPair.first.key);
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
				if ((mapPair.first.type == InputType::OnDown && controller->IsDown(mapPair.first.button)) ||
					(mapPair.first.type == InputType::Pressed && controller->IsPressed(mapPair.first.button)) ||
					(mapPair.first.type == InputType::OnRelease && controller->IsUp(mapPair.first.button)))
				{
					mapPair.second->Execute();
					inputPacket.controllerInputs[mapPair.first.controllerID].push_back(static_cast<int>(mapPair.first.button));
				}
			}
		}
	}

	SendClientInputsToServer(inputPacket);

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

void InputManager::ReceiveInputMultiplayer(const std::string& inputPacket)
{
	ClientInputPacket receivedPacket = DeserializePacket(inputPacket);
	ProcessReceivedPacket(receivedPacket);
}

void InputManager::SendClientInputsToServer(const ClientInputPacket& packet) const
{
	if (packet.pressedKeys.empty() &&
		packet.heldKeys.empty() &&
		packet.releasedKeys.empty() &&
		packet.controllerInputs.empty())
		return;


	// 1. Serialize the packet
	std::string serializedData = SerializePacket(packet);

	// 2. Send the serialized data over the network socket to the host
	ServerConnector::GetInstance().SendInputPacket(serializedData);
}

std::string InputManager::SerializePacket(const ClientInputPacket& packet) const
{
	std::ostringstream stream;

	// Serialize pressed keys
	for (const auto& key : packet.pressedKeys)
	{
		stream << key << " "; // Delimiting keys with space
	}
	stream << "|"; // Using '|' as delimiter between sections

	// Serialize held keys
	for (const auto& key : packet.heldKeys)
	{
		stream << key << " "; // Delimiting keys with space
	}
	stream << "|"; // Using '|' as delimiter between sections

	// Serialize released keys
	for (const auto& key : packet.releasedKeys)
	{
		stream << key << " ";
	}
	stream << "|";

	// Serialize controller inputs
	for (const auto& controllerInput : packet.controllerInputs)
	{
		stream << controllerInput.first << ":"; // Controller ID
		for (const auto& button : controllerInput.second)
		{
			stream << button << ",";
		}
		stream << ";"; // ';' to separate different controllers
	}
	stream << " ";

	return stream.str();
}

InputManager::ClientInputPacket InputManager::DeserializePacket(const std::string& data) const
{
	ClientInputPacket packet{};

	std::vector<std::string> sections;
	std::stringstream ss{};
	ss << data;
	std::string item;

	//Split all the data into sections
	while (std::getline(ss, item, '|'))
	{
		sections.push_back(item);
	}
	//error handle
	if (sections.size() < 4)
	{
		std::cout << "Received input packet has wrong format.\n";
		return packet;
	}


	// Deserialize pressed keys
	std::stringstream pressedKeys(sections[0]);
	while (std::getline(pressedKeys, item, ' '))
	{
		if (!item.empty())
		{
			packet.pressedKeys.push_back(std::stoi(item));
		}
	}

	// Deserialize held keys
	std::stringstream heldKeys(sections[1]);
	while (std::getline(heldKeys, item, ' '))
	{
		if (!item.empty())
		{
			packet.heldKeys.push_back(std::stoi(item));
		}
	}

	// Deserialize released keys
	std::stringstream releasedKeys(sections[2]);
	while (std::getline(releasedKeys, item, ' '))
	{
		if (!item.empty())
		{
			packet.releasedKeys.push_back(std::stoi(item));
		}
	}

	// Deserialize controller inputs
	std::stringstream controllerInput(sections[3]);
	while (std::getline(controllerInput, item, ';'))
	{
		if (!item.empty())
		{
			size_t pos = item.find(':');
			if (pos != std::string::npos)
			{
				int controllerID = std::stoi(item.substr(0, pos));
				std::stringstream buttons(item.substr(pos + 1));
				std::string button;

				while (std::getline(buttons, button, ','))
				{
					if (!button.empty())
					{
						packet.controllerInputs[controllerID].push_back(std::stoi(button));
					}
				}
			}
		}
	}

	return packet;
}

void InputManager::ProcessReceivedPacket(const ClientInputPacket& receivedPacket)
{
	// 1. Process Pressed Keys
	for (const auto& key : receivedPacket.pressedKeys)
	{
		auto iter = m_KeyboardActionMap.find({ key, InputType::OnDown });
		if (iter != m_KeyboardActionMap.end())
		{
			Minigin::AddTask([=](void) { iter->second->Execute(); });
		}
	}

	// 2. Process Held Keys
	for (const auto& key : receivedPacket.heldKeys)
	{
		auto iter = m_KeyboardActionMap.find({ key, InputType::Pressed });
		if (iter != m_KeyboardActionMap.end())
		{
			iter->second->Execute();
		}
	}

	// 3. Process Released Keys
	for (const auto& key : receivedPacket.releasedKeys)
	{
		auto iter = m_KeyboardActionMap.find({ key, InputType::OnRelease });
		if (iter != m_KeyboardActionMap.end())
		{
			iter->second->Execute();
		}
	}

	// 4. Process Controller Inputs
	for (const auto& controllerInput : receivedPacket.controllerInputs)
	{
		int controllerID = controllerInput.first;
		for (const auto& button : controllerInput.second)
		{
			for (const auto& mapPair : m_ControllerActionMap)
			{
				if (mapPair.first.controllerID == static_cast<unsigned int>(controllerID) &&
					static_cast<int>(mapPair.first.button) == button)
				{
					mapPair.second->Execute();
					break;
				}
			}
		}
	}
}
