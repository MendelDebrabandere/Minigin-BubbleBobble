#pragma once
#include "Command.h"

class StartCoopCommand final : public dae::Command
{
public:
	StartCoopCommand() = default;

	void Execute() override;
private:
};