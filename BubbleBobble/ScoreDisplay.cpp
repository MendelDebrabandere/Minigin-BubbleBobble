#include "ScoreDisplay.h"

#include "AvatarComponent.h"
#include "GameObject.h"

void ScoreDisplay::SetPlayer(AvatarComponent* player)
{
	m_Player = player;
	if (m_Player)
	{
		m_Player->m_Score.AddObserver(this);
	}
}

void ScoreDisplay::HandleEvent(FoodComponent::FoodType type)
{
	switch (type)
	{
	case FoodComponent::FoodType::Melon:
		m_score += 100;
		break;
	case FoodComponent::FoodType::Fries:
		m_score += 200;
		break;
	}
	std::cout << m_score << '\n';
	UpdateScoreText();
}

ScoreDisplay::~ScoreDisplay()
{
	if (m_Player)
	{
		m_Player->m_Score.RemoveObserver(this);
	}
}
