#include "ColliderComponent.h"

#include "GameObject.h"
#include "Renderer.h"


using namespace dae;

ColliderComponent::ColliderComponent()
	: Component()
{
}

void ColliderComponent::Update()
{
	m_Pos = GetOwner()->GetTransform()->GetWorldPosition();
}

void ColliderComponent::Render() const
{
	if (m_DrawDebug == false)
		return;

	const auto renderer = Renderer::GetInstance().GetSDLRenderer();

	SDL_Rect rect;
	rect.x = static_cast<int>(m_Pos.x);
	rect.y = static_cast<int>(m_Pos.y);
	rect.w = static_cast<int>(m_Size.x);
	rect.h = static_cast<int>(m_Size.y);

	SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(m_Color.r), static_cast<Uint8>(m_Color.g), static_cast<Uint8>(m_Color.b), static_cast<Uint8>(m_Color.a));
	SDL_RenderDrawRect(renderer, &rect);
}

bool ColliderComponent::IsOverlappingWith(const GameObject& other) const
{
	auto otherCollider = other.GetComponent<ColliderComponent>();
	if (otherCollider == nullptr)
		return false;


	const auto otherSize = otherCollider->GetSize();
	const auto otherPos = otherCollider->GetPos();

	if (m_Pos.x > otherPos.x + otherSize.x)
		return false;

	if (m_Pos.x + m_Size.x < otherPos.x)
		return false;

	if (m_Pos.y > otherPos.y + otherSize.y)
		return false;

	if (m_Pos.y + m_Size.y < otherPos.y)
		return false;

	return true;
}