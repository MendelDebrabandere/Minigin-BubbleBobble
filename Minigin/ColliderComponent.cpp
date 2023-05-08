#include "ColliderComponent.h"

#include "GameObject.h"
#include "Renderer.h"


using namespace dae;

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

std::pair<ColliderComponent::OverlapData, float> ColliderComponent::IsOverlappingWith(const ColliderComponent* other) const
{
    const auto otherSize = other->GetSize();
    const auto otherPos = other->GetPos();

    // Check if not overlapping
    if (m_Pos.x > otherPos.x + otherSize.x ||
        m_Pos.x + m_Size.x < otherPos.x ||
        m_Pos.y > otherPos.y + otherSize.y ||
        m_Pos.y + m_Size.y < otherPos.y)
    {
        return std::make_pair(OverlapData::Not, 0.f);
    }

    // Calculate overlap on each side
    float overlapLeft = m_Pos.x + m_Size.x - otherPos.x;
    float overlapRight = otherPos.x + otherSize.x - m_Pos.x;
    float overlapTop = m_Pos.y + m_Size.y - otherPos.y;
    float overlapBottom = otherPos.y + otherSize.y - m_Pos.y;

    // Find the minimum overlap
    float minOverlapX = std::min(overlapLeft, overlapRight);
    float minOverlapY = std::min(overlapTop, overlapBottom);

    // Return the side with minimum overlap
    if (minOverlapX < minOverlapY)
    {
        return (overlapLeft < overlapRight) ? std::make_pair(OverlapData::Left, overlapLeft)  : std::make_pair(OverlapData::Right, overlapRight);
    }
    else
    {
        return (overlapTop < overlapBottom) ? std::make_pair(OverlapData::Top, overlapTop)  : std::make_pair(OverlapData::Bottom, overlapBottom);
    }
}