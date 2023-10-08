#pragma once
#include "Command.h"

class ClientCommand final : public dae::Command
{
public:
	ClientCommand() = default;

	void Execute() override;
private:
};