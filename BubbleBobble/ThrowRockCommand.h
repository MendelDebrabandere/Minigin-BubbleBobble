#pragma once
#include "Command.h"
#include "Timer.h"

class ThrowRockCommand final : public dae::Command
{
public:
	explicit ThrowRockCommand(dae::GameObject* go)
		: m_pGo{ go }
	{
		m_LastTimeThrew = dae::Time::GetInstance().GetTotal();
	}

	void Execute() override;
private:
	dae::GameObject* m_pGo{};

	float m_LastTimeThrew;
};
