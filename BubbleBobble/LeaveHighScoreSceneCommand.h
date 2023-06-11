#pragma once
#include "Command.h"

class LeaveHighScoreSceneCommand final : public dae::Command
{
public:
	LeaveHighScoreSceneCommand() = default;

	void Execute() override;
private:
};