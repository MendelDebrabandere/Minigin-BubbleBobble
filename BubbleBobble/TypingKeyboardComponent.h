#pragma once
#include "Component.h"
#include "EventListener.h"

namespace dae
{
	class TextComponent;
}

class TypingKeyboardComponent final : public dae::Component,
										public dae::EventListener
{
public:
	TypingKeyboardComponent();
	~TypingKeyboardComponent() override;

	TypingKeyboardComponent(const TypingKeyboardComponent& other) = delete;
	TypingKeyboardComponent(TypingKeyboardComponent&& other) = delete;
	TypingKeyboardComponent& operator=(const TypingKeyboardComponent& other) = delete;
	TypingKeyboardComponent& operator=(TypingKeyboardComponent&& other) = delete;

	void OnEvent(const dae::Event& event) override;

	const std::string& GetInput() const;

private:
	std::string m_TextString{};

	dae::TextComponent* m_pText{};
};

