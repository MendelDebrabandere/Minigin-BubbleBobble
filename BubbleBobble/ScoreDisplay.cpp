#include "ScoreDisplay.h"

#include "AvatarComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <sstream>

void ScoreDisplay::Initialize()
{
	UpdateScoreText();
}

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

void ScoreDisplay::UpdateScoreText()
{

	// Get text component if its not there
	if (m_pText == nullptr)
	{
		m_pText = GetOwner()->GetComponent<dae::TextComponent>();

		if (m_pText == nullptr) return;
	}

	// Update text component
	std::stringstream scoreText{};

	scoreText << "Score: ";
	scoreText << m_score;

	m_pText->SetText(scoreText.str());
}

ScoreDisplay::~ScoreDisplay()
{
	//if (m_Player)
	//{
	//	m_Player->m_Score.RemoveObserver(this);
	//}
}
