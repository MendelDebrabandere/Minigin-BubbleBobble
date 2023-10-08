#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Singleton.h"
#include "XBox360Controller.h"
#include "Command.h"

namespace dae
{

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		XBox360Controller* GetController(unsigned int controllerIdx);

		enum class InputType
		{
			OnDown,
			Pressed,
			OnRelease
		};

		void AddControllerCommand(XBox360Controller::ControllerButton button, unsigned int controllerID, InputType type, std::unique_ptr<Command> pCommand);
		void AddKeyboardCommand(unsigned int keyboardKey, InputType type, std::unique_ptr<Command> pCommand);

		bool IsKeyboardKeyDown(unsigned int keyboardKey);

		void RemoveAllInputs();

		void ReceiveInputFromClient(const std::string& inputPacket);

	private:
		struct InputDataController
		{
			unsigned int controllerID{};
			XBox360Controller::ControllerButton button{};
			InputType type{};

			// Custom less-than operator for std::map
			bool operator<(const InputDataController& other) const
			{
				if (controllerID < other.controllerID) return true;
				if (controllerID > other.controllerID) return false;

				if (button < other.button) return true;
				if (button > other.button) return false;

				return type < other.type;
			}
		};

		struct InputDataKeyboard
		{
			unsigned int key{};
			InputType type{};

			// Custom less-than operator for std::map
			bool operator<(const InputDataKeyboard& other) const
			{
				if (key < other.key) return true;
				if (key > other.key) return false;

				return type < other.type;
			}
		};

		//For sending inputs to the host
		struct ClientInputPacket
		{
			std::vector<unsigned int> pressedKeys;  // List of pressed keys
			std::vector<unsigned int> heldKeys; // List of released keys
			std::vector<unsigned int> releasedKeys; // List of released keys
			std::map<int, std::vector<int>> controllerInputs; // Map of controller ID to a list of pressed buttons
		};
		void SendClientInputsToServer(const ClientInputPacket& packet) const;
		std::string SerializePacket(const ClientInputPacket& packet) const;
		ClientInputPacket DeserializePacket(const std::string& data) const;
		void ProcessReceivedPacket(const ClientInputPacket& receivedPacket);


		friend class Singleton<InputManager>;
		InputManager() = default;

		std::map<InputDataController, std::unique_ptr<Command>> m_ControllerActionMap{};
		std::vector<std::unique_ptr<XBox360Controller>> m_ControllerPtrs{};

		std::map<InputDataKeyboard, std::unique_ptr<Command>> m_KeyboardActionMap{};

		std::vector<unsigned int> m_PressedKeys{};
	};
}
