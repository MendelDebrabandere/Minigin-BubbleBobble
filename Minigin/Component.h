#pragma once
#include <memory>

namespace dae
{
	class Transform;
	class GameObject;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Render() {}

		virtual void Update() {}
		virtual void FixedUpdate() {}

		std::shared_ptr<Transform> GetTransform() const;
		std::shared_ptr<GameObject> GetOwner() const;
		void SetOwner(std::weak_ptr<GameObject> pParent);

	protected:
		std::weak_ptr<GameObject> m_pOwner{};
	};
}