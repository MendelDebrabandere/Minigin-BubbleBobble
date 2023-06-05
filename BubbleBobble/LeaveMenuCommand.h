#pragma once
#include "Command.h"

class LeaveMenuCommand final : public dae::Command
{
public:
	LeaveMenuCommand() = default;

	void Execute() override;
private:
};