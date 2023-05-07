#include "Renderer.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Timer.h"
#include <glm/vec2.hpp>

using namespace dae;

SpriteComponent::SpriteComponent()
	: Component()
{
}

void SpriteComponent::Update()
{
	m_RenderPos = m_pOwner->GetTransform()->GetWorldPosition();

	if (!m_Pause) // if not paused, update animation
	{
		m_CurrTime += Time::GetInstance().GetDelta();

		if (m_CurrTime >= m_AnimTimer)
		{
			++m_CurrIdx;
			if (m_CurrIdx >= m_EndIdx)
				m_CurrIdx = m_StartIdx;

			m_Rect.x = (m_CurrIdx % m_Columns) * m_Rect.w;
			m_Rect.y = (m_CurrIdx / m_Columns) * m_Rect.h;

			m_CurrTime = 0.f;
		}
	}

}

void SpriteComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_Texture, m_RenderPos.x, m_RenderPos.y, m_RenderWidth, m_RenderHeight, &m_Rect);
}

void SpriteComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void SpriteComponent::SetAnimVariables(int rows, int columns, float animTimer, int startIdx, int endIdx)
{
	m_Rows = rows;
	m_Columns = columns;
	m_AnimTimer = animTimer;
	m_CurrIdx = startIdx;
	m_StartIdx = startIdx;
	m_EndIdx = endIdx;

	if (m_EndIdx == 0)
		m_EndIdx = m_Columns * m_Rows;

	m_Rect.w = int(m_Texture->GetSize().x) / m_Columns;
	m_Rect.h = int(m_Texture->GetSize().y) / m_Rows;
	m_Rect.x = (m_CurrIdx % m_Columns) * m_Rect.w;
	m_Rect.y = (m_CurrIdx / m_Columns) * m_Rect.h;

	m_RenderWidth = float(m_Rect.w);
	m_RenderHeight = float(m_Rect.h);
}

void SpriteComponent::Scale(float value)
{
	m_RenderWidth *= value;
	m_RenderHeight *= value;
}

void SpriteComponent::Pause()
{
	m_Pause = true;
}
