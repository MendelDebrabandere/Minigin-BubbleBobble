#include "Component.h"
#include "GameObject.h"

std::shared_ptr<dae::Transform> dae::Component::GetTransform() const
{
	if (m_pOwner.expired()) return nullptr;

	return m_pOwner.lock()->GetTransform();
}

std::shared_ptr<dae::GameObject> dae::Component::GetOwner() const
{
	if (m_pOwner.expired()) return nullptr;

	return m_pOwner.lock();
}

void dae::Component::SetOwner(std::weak_ptr<GameObject> pParent)
{
	m_pOwner = pParent;
}