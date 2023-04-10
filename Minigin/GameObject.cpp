#include "GameObject.h"
#include "ResourceManager.h"
#include "Component.h"

using namespace dae;

void GameObject::Init()
{
	m_pTransform = AddComponent<Transform>();
}

void GameObject::Update()
{
	for (const auto component : m_Components)
	{
		component->Update();
	}
	for (auto child : m_pChildren)
	{
		child->Update();
	}
}

void GameObject::FixedUpdate()
{
	for (const auto component : m_Components)
	{
		component->FixedUpdate();
	}
	for (auto child : m_pChildren)
	{
		child->FixedUpdate();
	}
}

void GameObject::Render() const
{
	for (const auto& pRenderComponent : m_pTextures)
	{
		pRenderComponent->Render();
	}
	for (auto child : m_pChildren)
	{
		child->Render();
	}
}

void GameObject::SetParent(std::shared_ptr<GameObject> pParent)
{
	std::shared_ptr<GameObject> pOldParent{};
	if (m_pParent.expired()) pOldParent = m_pParent.lock();

	if (pOldParent)
	{
		if (pOldParent == pParent) return;

		// Remove itself from the children list of the previous parent
		for (int i{ static_cast<int>(pOldParent->m_pChildren.size() - 1) }; i >= 0; --i)
		{
			const auto pChild{ pOldParent->m_pChildren[i] };

			if (pChild.get() == this)
			{
				pOldParent->m_pChildren[i] = pOldParent->m_pChildren[pOldParent->m_pChildren.size() - 1];
				pOldParent->m_pChildren.pop_back();
				break;
			}
		}
	}
	else if(!pParent)
	{
		return;
	}

	
	m_pParent = pParent;

	if (pParent)
		pParent->m_pChildren.push_back(shared_from_this());

	auto pTransform{ GetTransform() };
	if (!pTransform)
		return;

	if (pParent)
	{
		// Set the local position to the position relative to the new parent
		auto pParentTransform{ pParent->GetTransform() };
		if (pParentTransform)
			pTransform->SetLocalPosition(pTransform->GetWorldPosition() - pParentTransform->GetWorldPosition());
	}
	else
	{
		// Set the local position to the world position
		pTransform->SetLocalPosition(pTransform->GetWorldPosition());
	}

}

std::shared_ptr<GameObject> GameObject::GetParent() const
{
	if (m_pParent.expired()) return nullptr;

	return m_pParent.lock();
}

void GameObject::Destroy()
{
	m_IsMarkedDead = true;

	// Destroy all children
	for (auto child : m_pChildren)
	{
		child->Destroy();
	}
}