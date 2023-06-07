#include "Renderer.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Timer.h"
#include <glm/vec2.hpp>

using namespace dae;

void SpriteComponent::Update()
{
	m_RenderPos = m_pOwner->GetTransform()->GetWorldPosition();

	if (!m_Pause || m_DoOnceAnim) // if not paused or DoOnce is true, update animation
	{
		m_CurrTime += Time::GetInstance().GetDelta();

		if (m_CurrTime >= m_AnimTimer)
		{
			//UpdateCurrIdx
			++m_CurrIdx;
			if (m_CurrIdx >= m_EndIdx)
			{
				//Check if it is doing a DoOnceAnim
				if (m_DoOnceAnim)
				{	//Reset to normal variables and turn DoOnce off
					m_DoOnceAnim = false;
					m_EndIdx = m_DoOnceEndIdx;
					m_AnimTimer = m_DoOnceAnimTimer;
				}
				m_CurrIdx = m_StartIdx;
			}

			//Move rect
			m_Rect.x = (m_CurrIdx % m_Columns) * m_Rect.w;
			m_Rect.y = (m_CurrIdx / m_Columns) * m_Rect.h;

			m_CurrTime = 0.f;
		}
	}
}

void SpriteComponent::Render() const
{
	if (m_Show)
	{
		if (m_FlipTexture == false)
			Renderer::GetInstance().RenderTexture(*m_Texture,
													m_RenderPos.x + m_RenderOffset.x,
													m_RenderPos.y + m_RenderOffset.y,
													m_RenderWidth,
													m_RenderHeight,
													&m_Rect);
		else
			Renderer::GetInstance().RenderTexture(*m_Texture,
													m_RenderPos.x + m_RenderOffset.x,
													m_RenderPos.y + m_RenderOffset.y,
													m_RenderWidth,
													m_RenderHeight,
													&m_Rect,
													SDL_FLIP_HORIZONTAL);
	}
}

void SpriteComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void SpriteComponent::SetAnimVariables(int rows, int columns, float animTimer, int startIdx, int endIdx)
{
	//if it is in a do once cycle
	if (m_DoOnceAnim)
	{
		//cancel it and just do the new animation
		m_DoOnceAnim = false;
	}

	//Set all the variables
	m_CurrTime = 0.f;
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

void SpriteComponent::Pause(bool value)
{
	m_Pause = value;
}

void SpriteComponent::FlipTexture(bool value)
{
	m_FlipTexture = value;
}

void SpriteComponent::DoOnceAnim(float animTimer, int startIdx, int endIdx)
{
	if (m_DoOnceAnim)
	{
		//first reset variables
		m_EndIdx = m_DoOnceEndIdx;
		m_AnimTimer = m_DoOnceAnimTimer;
	}                                             
	m_DoOnceAnim = true;
	m_CurrTime = 0.f;

	//Save curr variables in the DoOnce variables
	m_DoOnceEndIdx = m_EndIdx;
	m_DoOnceAnimTimer = m_AnimTimer;

	//Store the new values in the main ones
	m_CurrIdx = startIdx;
	m_EndIdx = endIdx;
	m_AnimTimer = animTimer;

	//Move rect
	m_Rect.x = (m_CurrIdx % m_Columns) * m_Rect.w;
	m_Rect.y = (m_CurrIdx / m_Columns) * m_Rect.h;
}

void SpriteComponent::ToggleVisuals(bool value)
{
	m_Show = value;
}

bool SpriteComponent::IsDoingOnce() const
{
	return m_DoOnceAnim;
}

glm::vec2 SpriteComponent::GetSize() const
{
	return glm::vec2(m_RenderWidth, m_RenderHeight);
}

void SpriteComponent::SetRenderOffset(const glm::vec2& offset)
{
	m_RenderOffset = offset;
}
