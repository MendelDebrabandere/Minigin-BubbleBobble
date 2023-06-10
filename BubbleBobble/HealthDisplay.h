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
	void SetSubject(dae::Subject<int>* healthSubj);

	int GetHP() const;

private:

	void HandleEvent(int healthDelta) override;
	void OnSubjectDestroy() override {}
	void UpdateText();

	int m_HP{};
	dae::Subject<int>* m_pSubject{};

	dae::TextComponent* m_pText{};
};

