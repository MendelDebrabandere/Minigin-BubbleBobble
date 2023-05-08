#pragma once
#include "Command.h"

class JumpCommand final : public dae::Command
{
public:
	explicit JumpCommand(dae::GameObject* go, float speed)
		:m_pGo{ go }
		, m_Speed{ speed }
	{}

	void Execute() override;
private:
	dae::GameObject* m_pGo{};
	float m_Speed{};
};