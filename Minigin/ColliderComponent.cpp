#include "ColliderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneManager.h"


using namespace dae;

void ColliderComponent::FixedUpdate()
{
    UpdatePos();
    CheckForOverlaps();
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

bool ColliderComponent::IsOverlappingWith(const ColliderComponent* other)
{
    //make sure m_Pos is up to date
    UpdatePos();

    const auto otherSize = other->GetSize();
    const auto otherPos = other->GetOwner()->GetTransform()->GetWorldPosition();

    // Check if not overlapping
    if (m_Pos.x > otherPos.x + otherSize.x ||
        m_Pos.x + m_Size.x < otherPos.x ||
        m_Pos.y > otherPos.y + otherSize.y ||
        m_Pos.y + m_Size.y < otherPos.y)
    {
        return false;
    }
    return true;
}

std::pair<ColliderComponent::OverlapData, float> ColliderComponent::IsOverlappingWithDirectional(const ColliderComponent* other)
{
    //make sure m_Pos is up to date
    UpdatePos();

    const auto otherSize = other->GetSize();
    const auto otherPos = other->GetOwner()->GetTransform()->GetWorldPosition();

    // Check if not overlapping
    if (m_Pos.x > otherPos.x + otherSize.x ||
        m_Pos.x + m_Size.x < otherPos.x ||
        m_Pos.y > otherPos.y + otherSize.y ||
        m_Pos.y + m_Size.y < otherPos.y)
    {
        return std::make_pair(OverlapData::Not, 0.f);
    }

    std::vector<std::pair<OverlapData, float>> overlappingSides{};

    // Calculate overlap on each side
    overlappingSides.emplace_back(OverlapData::Left, -1 * (m_Pos.x - otherPos.x - otherSize.x));
    overlappingSides.emplace_back(OverlapData::Right, m_Pos.x + m_Size.x - otherPos.x);
    overlappingSides.emplace_back(OverlapData::Top, -1 * (m_Pos.y - otherPos.y - otherSize.y));
    overlappingSides.emplace_back(OverlapData::Bottom, m_Pos.y + m_Size.y - otherPos.y);

    for (auto& pair : overlappingSides)
    {
        if (pair.second < 0.f)
        {
            pair.second = FLT_MAX;
        }
    }


    std::pair smallestOverlap{ OverlapData::Not, FLT_MAX };


    for (auto& pair : overlappingSides)
    {
        if (pair.second < smallestOverlap.second)
        {
            smallestOverlap = pair;
        }
    }

    return smallestOverlap;

}

void ColliderComponent::SetSize(const glm::vec2& val)
{
     m_Size = val;
}

void ColliderComponent::UpdatePos()
{
    m_Pos = m_pOwner->GetTransform()->GetWorldPosition();
}

void ColliderComponent::SetOverlapFunction(std::function<void(GameObject*)> overlapFunction)
{
    m_OverlapFunction = std::move(overlapFunction);
}

void ColliderComponent::CheckForOverlaps()
{
    // if it has an overlap function
    if (m_OverlapFunction)
    {
        // for all objects in the scene
        Scene* scene = SceneManager::GetInstance().GetActiveScene();
        for (auto& object : scene->GetAllObjects())
        {
            if (object.get() == m_pOwner)
                continue;

            //if they have a collider
            ColliderComponent* otherCollComp = object->GetComponent<ColliderComponent>();
            if (otherCollComp)
            {
	            //if they overlap
                if (IsOverlappingWith(otherCollComp))
                {
	                //Call the overlapfunction
                    m_OverlapFunction(otherCollComp->GetOwner());
                }
            }
        }
    }
}