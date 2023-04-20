#include "ScoreComponent.h"
#include "Subject.h"
#include "Time.h"

using namespace dae;

void ScoreComponent::SetScore(int amount)
{
	m_Score = amount;
}

void ScoreComponent::AddScore(int amount)
{
	m_Score += amount;
}

int ScoreComponent::GetScore() const
{
	return m_Score;
}
