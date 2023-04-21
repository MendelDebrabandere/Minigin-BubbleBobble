#include "ScoreDisplay.h"
#include "Hero.h"


using namespace dae;

ScoreDisplay::ScoreDisplay(Hero* hero)
	:m_pHero{hero}
{
}

ScoreDisplay::~ScoreDisplay()
{
	if (m_pHero)
		m_pHero->foundLoot.RemoveObserver(this);
}


void ScoreDisplay::HandleEvent(LootType type)
{
	switch (type)
	{
	case LootType::Pellet:
		m_score += 10;
		break;
	case LootType::SuperPellet:
		m_score += 100;
		break;
	}
	UpdateScoreText();
}