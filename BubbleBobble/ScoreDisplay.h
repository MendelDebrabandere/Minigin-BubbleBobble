#pragma once
#include "Component.h"
#include "FoodComponent.h"
#include "Subject.h"

class AvatarComponent;

class ScoreDisplay final : public dae::Component, public dae::Observer<FoodComponent::FoodType>
{
public:
	ScoreDisplay() = default;
	virtual ~ScoreDisplay();

	ScoreDisplay(const ScoreDisplay& other) = delete;
	ScoreDisplay(ScoreDisplay&& other) = delete;
	ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
	ScoreDisplay& operator=(ScoreDisplay&& other) = delete;

	void SetPlayer(AvatarComponent* player);

private:

	void HandleEvent(FoodComponent::FoodType type) override;
	void OnSubjectDestroy() override {}
	void UpdateScoreText() {}

	int m_score{};
	AvatarComponent* m_Player{};

};
