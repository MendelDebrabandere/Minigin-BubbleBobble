#include "HealthDisplay.h"

#include "AvatarComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <sstream>

#include "EventQueue.h"

void HealthDisplay::Initialize()
{
	m_HP = 3;
	UpdateText();
}

void HealthDisplay::SetSubject(dae::Subject<int>* healthSubj)
{
	m_pSubject = healthSubj;
	if (m_pSubject)
	{
		m_pSubject->AddObserver(this);
	}
}

int HealthDisplay::GetHP() const
{
	return m_HP;
}

rapidjson::Value HealthDisplay::Serialize(rapidjson::Document::AllocatorType& allocator) const
{
	rapidjson::Value objectValue(rapidjson::kObjectType);

	// Serialize the health points (HP).
	objectValue.AddMember("HP", m_HP, allocator);

	return objectValue;
}

void HealthDisplay::Deserialize(const rapidjson::Value& value)
{
	// Deserialize the health points (HP).
	if (value.HasMember("HP")) 
		m_HP = value["HP"].GetInt();
}


void HealthDisplay::HandleEvent(int healthDelta)
{
	m_HP += healthDelta;

	if (m_HP < 0)
 		dae::EventQueue::GetInstance().SendEvent(dae::Event{ "PlayerDied" });
	else
		UpdateText();
}

void HealthDisplay::OnSubjectDestroy()
{
	m_pSubject = nullptr;
}

void HealthDisplay::UpdateText()
{

	// Get text component if its not there
	if (m_pText == nullptr)
	{
		m_pText = GetOwner()->GetComponent<dae::TextComponent>();

		if (m_pText == nullptr) return;
	}

	// Update text component
	std::stringstream healthText{};

	healthText << "Lives: ";
	healthText << m_HP;

	m_pText->SetText(healthText.str());
}

HealthDisplay::~HealthDisplay()
{
	if (m_pSubject)
	{
		m_pSubject->RemoveObserver(this);
	}
}
