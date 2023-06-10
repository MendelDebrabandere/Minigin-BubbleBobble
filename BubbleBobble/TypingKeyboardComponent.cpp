#include "TypingKeyboardComponent.h"
#include <memory>

#include "EventQueue.h"
#include "GameObject.h"
#include "Timer.h"
#include "TextComponent.h"

TypingKeyboardComponent::TypingKeyboardComponent()
{
	dae::EventQueue::GetInstance().AddListener(this);
}

TypingKeyboardComponent::~TypingKeyboardComponent()
{
	dae::EventQueue::GetInstance().RemoveListener(GetId());
}

void TypingKeyboardComponent::OnEvent(const dae::Event& event)
{
	//if the length is one that means it is an input from the inputmanager
	if (event.name.length() == 1)
	{
		m_TextString.append(event.name);

		// UPDATE TEXT PART
		// Get text component if its not there
		if (m_pText == nullptr)
		{
			m_pText = GetOwner()->GetComponent<dae::TextComponent>();

			if (m_pText == nullptr) return;
		}

		m_pText->SetText(m_TextString);
	}
}
