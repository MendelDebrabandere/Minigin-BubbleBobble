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
		m_Player->m_FoodPickup.AddObserver(this);
	}
}

int ScoreDisplay::GetScore() const
{
	return m_score;
}

rapidjson::Value ScoreDisplay::Serialize(rapidjson::Document::AllocatorType& allocator) const
{
	rapidjson::Value objectValue(rapidjson::kObjectType);

	// Serialize the score.
	objectValue.AddMember("score", m_score, allocator);

	return objectValue;
}


void ScoreDisplay::Deserialize(const rapidjson::Value& value)
{
	// Deserialize the score.
	if (value.HasMember("score"))
		m_score = value["score"].GetInt();
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
	UpdateScoreText();
}

void ScoreDisplay::OnSubjectDestroy()
{
	m_Player = nullptr;
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
	if (m_Player)
	{
		m_Player->m_FoodPickup.RemoveObserver(this);
	}
}
