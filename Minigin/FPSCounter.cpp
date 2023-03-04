#include "FPSCounter.h"
#include <iosfwd>
#include "Time.h"
#include "TextObject.h"
#include "Font.h"

dae::FPSCounter::FPSCounter()
{
	const std::shared_ptr<Font> font{ new Font("C:/Users/mende/OneDrive/Bureaublad/Game dev stuff/Programming4/minigin-1.1.1/Data/Lingua.otf", 20)};
	m_pText = new TextObject(std::string(), font);

	m_pText->SetPosition(5, 25);
}

dae::FPSCounter::~FPSCounter()
{
	delete m_pText;
	m_pText = nullptr;
}

void dae::FPSCounter::Render()
{
	m_pText->Render();
}

void dae::FPSCounter::Update()
{
	++m_AmountOfPassedFrames;

	// Every updateInterval, update the text to the average FPS of the interval
	m_AccuSec += Time::GetInstance().GetDelta();
	if (m_AccuSec >= m_UpdateInterval)
	{
		m_AccuSec -= m_UpdateInterval;

		std::stringstream fpsText{};

		fpsText << static_cast<int>(m_AmountOfPassedFrames / m_UpdateInterval);
		fpsText << " FPS";

		m_pText->SetText(fpsText.str());

		m_pText->Update();

		m_AmountOfPassedFrames = 0;
	}
}
