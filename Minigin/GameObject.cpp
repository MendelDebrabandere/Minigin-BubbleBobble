#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

using namespace dae;

dae::GameObject::~GameObject()
{
	if (m_Component)
		delete m_Component;
}

void dae::GameObject::Update() { if (m_Component) m_Component->Update(); }

void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);

	if (m_Component)
		m_Component->Render();
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

bool GameObject::RemoveComponent()
{
	if (m_Component)
	{
		delete m_Component;
		m_Component = nullptr;
		return true;
	}
	return false;
}

bool dae::GameObject::HasComponent() const
{
	return m_Component;
}
