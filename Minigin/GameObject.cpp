#include "GameObject.h"
#include "ResourceManager.h"
#include "Component.h"

using namespace dae;

void GameObject::Init()
{
	m_pTransform = AddComponent<Transform>();
}

void GameObject::FixedUpdate()
{
	for (const auto& component : m_Components)
	{
		component->FixedUpdate();
	}
	for (const auto& child : m_pChildren)
	{
		child->FixedUpdate();
	}
}

void GameObject::Update()
{
	for (const auto& component : m_Components)
	{
		component->Update();
	}
	for (const auto& child : m_pChildren)
	{
		child->Update();
	}
}

void GameObject::Render() const
{
	for (const auto& pComponent : m_Components)
	{
		pComponent->Render();
	}
	for (const auto& child : m_pChildren)
	{
		child->Render();
	}
}

void GameObject::SetParent(GameObject* pParent)
{
	GameObject* pOldParent{};

	if (pOldParent)
	{
		if (pOldParent == pParent) return;

		// Remove itself from the children list of the previous parent
		for (int i{ static_cast<int>(pOldParent->m_pChildren.size() - 1) }; i >= 0; --i)
		{
			const auto& pChild{ pOldParent->m_pChildren[i] };

			if (pChild.get() == this)
			{
				pOldParent->m_pChildren[i] = std::move(pOldParent->m_pChildren[pOldParent->m_pChildren.size() - 1]);
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
		pParent->m_pChildren.push_back(std::unique_ptr<GameObject>(this));

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

GameObject* GameObject::GetParent() const
{
	if (m_pParent) return nullptr;

	return m_pParent;
}

void GameObject::Destroy()
{
	m_IsMarkedDead = true;

	// Destroy all children
	for (const auto& child : m_pChildren)
	{
		child->Destroy();
	}
}

GameObject* GameObject::CreateGameObject()
{
	auto pGameObject{ std::make_unique<GameObject>() };
	pGameObject->Init();

	const auto pGameObjectPtr{ pGameObject.get() };

	pGameObject->m_pParent = this;
	m_pChildren.push_back(std::move(pGameObject));

	return pGameObjectPtr;
}
