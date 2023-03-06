#include "Transform.h"
#include "GameObject.h"

void dae::Transform::SetWorldPosition(const glm::vec2& position)
{
	m_LocalPosition += position - GetWorldPosition();
	EnableChangedFlag();
}

const glm::vec2& dae::Transform::GetWorldPosition()
{
	if (m_HasChanged) UpdateWorldPosition();

	return m_WorldPosition;
}

void dae::Transform::SetLocalPosition(float x, float y)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;

	EnableChangedFlag();
}

void dae::Transform::SetLocalPosition(const glm::vec2& position)
{
	m_LocalPosition = position;

	EnableChangedFlag();
}

void dae::Transform::UpdateWorldPosition()
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

void dae::Transform::SetWorldPosition(float x, float y)
{
	const glm::vec2& worldPos{ GetWorldPosition() };

	m_LocalPosition.x += x - worldPos.x;
	m_LocalPosition.y += y - worldPos.y;

	EnableChangedFlag();
}


void dae::Transform::Translate(float x, float y)
{
	m_LocalPosition.x += x;
	m_LocalPosition.y += y;

	EnableChangedFlag();
}

void dae::Transform::EnableChangedFlag()
{
	m_HasChanged = true;

	// If no parent exists, stop here
	const auto pParent{ GetOwner() };
	if (!pParent) return;

	// Change the HasChanged flag of every child
	const auto& pChildren{ pParent->GetChildren() };
	for (const auto& pWeakChild : pChildren)
	{
		if (pWeakChild.expired()) continue;

		const auto pChild{ pWeakChild.lock() };

		const auto pTransform{ pChild->GetTransform() };
		if (!pTransform) continue;

		pTransform->EnableChangedFlag();
	}
}