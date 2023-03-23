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

		bool SetActionToObject(GameObject& object) { m_Object = &object; }
		
		XBox360Controller* GetController(unsigned int controllerIdx);

		template <class T>
		void AddControllerCommands(GameObject* go, XBox360Controller::ControllerButton button, unsigned int controllerID);
	private:
		GameObject* m_Object{};

		std::map<std::pair<unsigned int, XBox360Controller::ControllerButton>, std::unique_ptr<Command>> m_ActionMap{};
		std::vector<std::unique_ptr<XBox360Controller>> m_ControllerPtrs{};

	};



	template<class T>
	inline void InputManager::AddControllerCommands(GameObject* go, XBox360Controller::ControllerButton button, unsigned int controllerID)
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
		m_ActionMap[std::pair(controllerID, button)] = std::make_unique<T>(go);


	}
}
