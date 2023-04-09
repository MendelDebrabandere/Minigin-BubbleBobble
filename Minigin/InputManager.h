#pragma once
#include <memory>
#include <map>
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

		void AddControllerCommand(XBox360Controller::ControllerButton button, unsigned int controllerID, std::unique_ptr<Command> pCommand);
		void AddKeyboardCommand(unsigned int keyboardKey, std::unique_ptr<Command> pCommand);

		enum class InputType
		{
			OnKeyDown,
			Pressed,
			OnRelease
		};

	private:
		std::map<std::pair<unsigned int, XBox360Controller::ControllerButton>, std::unique_ptr<Command>> m_ControllerActionMap{};
		std::vector<std::unique_ptr<XBox360Controller>> m_ControllerPtrs{};

		std::map<unsigned int, std::unique_ptr<Command>> m_KeyboardActionMap{};
	};
}
