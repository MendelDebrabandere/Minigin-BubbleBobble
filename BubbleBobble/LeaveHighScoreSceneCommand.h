#pragma once
#include "Command.h"

class LeaveHighScoreSceneCommand final : public dae::Command
{
public:
	explicit LeaveHighScoreSceneCommand(int score)
		:m_Score{score}
	{}

	void Execute() override;
private:
	int m_Score{};
};