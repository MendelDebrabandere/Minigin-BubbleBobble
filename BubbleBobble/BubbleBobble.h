#pragma once

class BubbleBobble final
{
public:
	explicit BubbleBobble() = delete;
	~BubbleBobble() = delete;
	BubbleBobble(const BubbleBobble&) = delete;
	BubbleBobble(BubbleBobble&&) = delete;
	BubbleBobble& operator=(const BubbleBobble&) = delete;
	BubbleBobble& operator=(BubbleBobble&&) = delete;

	static void Create();

private:
	static void MakeMainMenu();
	static void MakeAllLevels();
};
