#include "Component.h"
#include "GameObject.h"

dae::GameObject* dae::Component::GetOwner() const
{
	return m_pOwner;
}

void dae::Component::SetOwner(GameObject* pParent)
{
	m_pOwner = pParent;
}