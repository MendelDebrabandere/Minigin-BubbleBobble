#pragma once
#include "Command.h"
#include "GameObject.h"

class ShootBubbleCommand final : public dae::Command
{
public:
	explicit ShootBubbleCommand(dae::GameObject* go)
		: m_pGo{ go }
	{}

	void Execute() override;
private:
	dae::GameObject* m_pGo{};
};
