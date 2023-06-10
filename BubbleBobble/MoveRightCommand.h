#pragma once
#include "Command.h"

class MoveRightCommand final : public dae::Command
{
public:
	explicit MoveRightCommand(dae::GameObject* go, float speed)
		:m_pGo{ go }
		, m_Speed{ speed }
	{}

	void Execute() override;
private:
	void Move();

	dae::GameObject* m_pGo{};
	float m_Speed{};
};
