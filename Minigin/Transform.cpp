#include "Transform.h"
#include "GameObject.h"

using namespace dae;

void Transform::SetWorldPosition(float x, float y)
{
	const glm::vec2& worldPos{ GetWorldPosition() };

	SetLocalPosition(m_LocalPosition.x + (x - worldPos.x),
					m_LocalPosition.y + (y - worldPos.y));
}


void Transform::SetWorldPosition(const glm::vec2& position)
{
	SetWorldPosition(position.x, position.y);
}

const glm::vec2& Transform::GetWorldPosition()
{
	if (m_HasChanged) UpdateWorldPosition();

	return m_WorldPosition;
}

void Transform::SetLocalPosition(float x, float y)
{
	if (std::fabs(m_LocalPosition.x - x) < FLT_EPSILON)
	{
		if (m_LocalPosition.x < x)
			m_FacingRight = true;
		else
			m_FacingRight = false;
	}

	m_LocalPosition.x = x;
	m_LocalPosition.y = y;

	EnableChangedFlag();
}

void Transform::SetLocalPosition(const glm::vec2& position)
{
	SetLocalPosition(position.x, position.y);
}

void Transform::UpdateWorldPosition()
{
	//This line comes first because there are multiple exits in the function
	m_HasChanged = false;

	const auto pParent{ GetOwner()->GetParent() };

	// If no parent exist, use the local position as world position
	if (pParent == nullptr)
	{
		m_WorldPosition = m_LocalPosition;
		return;
	}

	const auto pParentTransform{ pParent->GetTransform() };

	// If no parent transform exist, use the local position as world position
	if (pParentTransform == nullptr)
	{
		m_WorldPosition = m_LocalPosition;
		return;
	}

	// Calculate the world position using the position of the parent
	m_WorldPosition = pParentTransform->GetWorldPosition() + m_LocalPosition;
}

void Transform::Translate(float x, float y)
{
	SetLocalPosition(m_LocalPosition.x + x,
					m_LocalPosition.y + y);
}

void Transform::Translate(glm::vec2 vec)
{
	Translate(vec.x, vec.y);
}


bool Transform::GetFacingRight() const
{
	return m_FacingRight;
}

void Transform::EnableChangedFlag()
{
	m_HasChanged = true;

	// If no parent exists, stop here
	const auto pParent{ GetOwner() };
	if (!pParent) return;

	// Change the HasChanged flag of every child
	const auto& pChildren{ pParent->GetChildren() };
	for (const auto& pChild : pChildren)
	{
		const auto pTransform{ pChild->GetTransform() };
		if (!pTransform) continue;

		pTransform->EnableChangedFlag();
	}
}