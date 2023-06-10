#pragma once
#include "Command.h"

class StartVersusCommand final : public dae::Command
{
public:
	StartVersusCommand() = default;

	void Execute() override;
private:
};