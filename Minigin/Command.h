#pragma once
#include "GameObject.h"

namespace dae
{
	class Command
	{
	public:
		explicit Command(GameObject* go){ m_pGameObject = go; }
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command& operator=(const Command& rhs) = delete;
		Command(Command&& other) = delete;
		Command& operator=(Command&& rhs) = delete;


		virtual void Execute(unsigned int controllerIdx) = 0;
	protected:
		GameObject* m_pGameObject{};
	};

	class MoveCommand final: public Command
	{
	public:
		explicit MoveCommand(GameObject* go):Command(go) {}

		void Execute(unsigned int controllerIdx) override;
	};
}













