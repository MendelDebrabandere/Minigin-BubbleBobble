#include <unordered_set>

#include "ColliderComponent.h"
#include "Singleton.h"

namespace dae
{
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void AddCollider(ColliderComponent* collider);
		void RemoveCollider(ColliderComponent* collider);

		void FixedUpdate();
	private:
		enum class EndpointType { Start, End };

		struct Endpoint {
			ColliderComponent* object;
			EndpointType type;
			float value;
		};

		std::vector<ColliderComponent*> m_Colliders;

		std::vector<Endpoint> m_EndpointsX{};

		void SweepAndPrune();

		bool isActiveOnBothAxes(ColliderComponent* object);
	};
}

