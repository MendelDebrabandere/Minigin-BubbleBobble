#pragma once
#include "FoodComponent.h"
#include "Subject.h"

namespace dae
{
	class TextComponent;
}

class AvatarComponent;

class HealthDisplay final : public dae::Component, public dae::Observer<int>
{
public:
	HealthDisplay() = default;
	~HealthDisplay() override;

	HealthDisplay(const HealthDisplay& other) = delete;
	HealthDisplay(HealthDisplay&& other) = delete;
	HealthDisplay& operator=(const HealthDisplay& other) = delete;
	HealthDisplay& operator=(HealthDisplay&& other) = delete;

	void Initialize() override;
	void SetPlayer(AvatarComponent* player);

	int GetHP() const;

private:

	void HandleEvent(int healthDelta) override;
	void OnSubjectDestroy() override {}
	void UpdateText();

	int m_HP{};
	AvatarComponent* m_Player{};

	dae::TextComponent* m_pText{};
};

