#include "CollisionManager.h"

#include <algorithm>
#include <chrono>

#include "PhysicsComponent.h"
#include "Scene.h"
#include "SceneManager.h"

using namespace dae;

void CollisionManager::AddCollider(ColliderComponent* collider)
{
    m_Colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(ColliderComponent* collider)
{
    auto it = std::find(m_Colliders.begin(), m_Colliders.end(), collider);
    if (it != m_Colliders.end())
    {
        m_Colliders.erase(it);
    }
}

void CollisionManager::FixedUpdate()
{
    auto start = std::chrono::high_resolution_clock::now();
    // Update the positions of all the endpoints in m_EndpointsX and m_EndpointsY
    m_EndpointsX.clear();

    for (ColliderComponent* collider : m_Colliders)
    {
        glm::vec2 pos = collider->GetPos();
        glm::vec2 size = collider->GetSize();

        m_EndpointsX.push_back({ collider, EndpointType::Start, pos.x});
        m_EndpointsX.push_back({ collider, EndpointType::End, pos.x + size.x });
    }

    // Then, you could call SweepAndPrune() to check for collisions
    SweepAndPrune();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "FixedUpdate took " << elapsed.count() << " ms\n";
}

void CollisionManager::SweepAndPrune()
{
    // Sort the endpoints
    std::sort(m_EndpointsX.begin(), m_EndpointsX.end(), [](const Endpoint& a, const Endpoint& b) { return a.value < b.value; });

    std::vector<ColliderComponent*> activeList;

    // Iterate over the sorted endpoints and update the active set on the X-axis.
    // When you encounter the end endpoint of a bounding box, check for overlaps with all boxes in the active set.
    for (const Endpoint& endpoint : m_EndpointsX)
    {
        if (endpoint.type == EndpointType::Start)
        {
            for (ColliderComponent* active_obj : activeList)
            {
                if (active_obj->CheckForOverlap(endpoint.object))
                    endpoint.object->CheckForOverlap(active_obj);
            }
            activeList.push_back(endpoint.object);
        }
        else
        {
            activeList.erase(std::remove(activeList.begin(), activeList.end(), endpoint.object), activeList.end());
        }
    }
}
