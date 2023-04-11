#include "ScoreComponent.h"
#include "Subject.h"
#include "Time.h"

using namespace dae;

void ScoreComponent::SetScore(int amount)
{
	m_Score = amount;
	Subject::GetInstance().Notify(m_pOwner, Observer::Event::ScoreUpdated);
}

void ScoreComponent::AddScore(int amount)
{
	m_Score += amount;
	Subject::GetInstance().Notify(m_pOwner, Observer::Event::ScoreUpdated);
}

int ScoreComponent::GetScore() const
{
	return m_Score;
}
