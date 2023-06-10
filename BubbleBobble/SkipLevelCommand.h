#pragma once
#include "Command.h"

class SkipLevelCommand final : public dae::Command
{
public:
	explicit SkipLevelCommand()
	{}

	void Execute() override;
private:
	
};
