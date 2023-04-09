#pragma once
#include "GameObject.h"

namespace dae
{
	class Command
	{
	public:
		explicit Command() = default;
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command& operator=(const Command& rhs) = delete;
		Command(Command&& other) = delete;
		Command& operator=(Command&& rhs) = delete;


		virtual void Execute() = 0;
	};

#pragma region MoveCommands
	class MoveUpCommand final: public Command
	{
	public:
		explicit MoveUpCommand(GameObject* go, float speed)
			:m_pGo{go}
			,m_Speed{speed}
			{}

		void Execute() override;
	private:
		GameObject* m_pGo{};
		float m_Speed{};
	};

	class MoveDownCommand final : public Command
	{
	public:
		explicit MoveDownCommand(GameObject* go, float speed)
			:m_pGo{ go }
			, m_Speed{ speed }
		{}

		void Execute() override;
	private:
		GameObject* m_pGo{};
		float m_Speed{};
	};

	class MoveLeftCommand final : public Command
	{
	public:
		explicit MoveLeftCommand(GameObject* go, float speed)
			:m_pGo{ go }
			, m_Speed{ speed }
		{}

		void Execute() override;
	private:
		GameObject* m_pGo{};
		float m_Speed{};
	};

	class MoveRightCommand final : public Command
	{
	public:
		explicit MoveRightCommand(GameObject* go, float speed)
			:m_pGo{ go }
			, m_Speed{ speed }
		{}

		void Execute() override;
	private:
		GameObject* m_pGo{};
		float m_Speed{};
	};
#pragma endregion
}


