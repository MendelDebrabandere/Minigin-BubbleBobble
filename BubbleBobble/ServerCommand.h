#pragma once
#include "Command.h"

class ServerCommand final : public dae::Command
{
public:
	ServerCommand() = default;

	void Execute() override;
private:
};