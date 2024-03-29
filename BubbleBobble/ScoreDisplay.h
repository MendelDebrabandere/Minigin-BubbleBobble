#pragma once
#include "FoodComponent.h"
#include "Subject.h"

namespace dae
{
	class TextComponent;
}

class AvatarComponent;

class ScoreDisplay final : public dae::Component, public dae::Observer<FoodComponent::FoodType>
{
public:
	ScoreDisplay() = default;
	~ScoreDisplay() override ;

	ScoreDisplay(const ScoreDisplay& other) = delete;
	ScoreDisplay(ScoreDisplay&& other) = delete;
	ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
	ScoreDisplay& operator=(ScoreDisplay&& other) = delete;

	void Initialize() override;
	void SetPlayer(AvatarComponent* player);

	int GetScore() const;

	virtual rapidjson::Value Serialize(rapidjson::Document::AllocatorType&) const override;
	virtual void Deserialize(const rapidjson::Value&) override;

private:

	void HandleEvent(FoodComponent::FoodType type) override;
	void OnSubjectDestroy() override;
	void UpdateScoreText();

	int m_score{};
	AvatarComponent* m_Player{};

	dae::TextComponent* m_pText{};
};

