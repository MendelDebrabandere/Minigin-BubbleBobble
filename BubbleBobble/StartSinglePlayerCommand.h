#pragma once
#include "Command.h"

class StartSinglePlayerCommand final : public dae::Command
{
public:
	StartSinglePlayerCommand() = default;

	void Execute() override;
private:
};