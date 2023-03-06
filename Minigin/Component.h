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
		virtual void LateUpdate() {}
		virtual void FixedUpdate() {}

		//template<class T>
		//std::shared_ptr<T> GetComponent() const;
		std::shared_ptr<Transform> GetTransform() const;
		std::shared_ptr<GameObject> GetOwner() const;
		void SetOwner(std::weak_ptr<GameObject> pParent);

	private:

		std::weak_ptr<GameObject> m_pOwner{};
	};

	//template<class T>
	//inline std::shared_ptr<T> Component::GetComponent() const
	//{
	//	static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

	//	if (m_pOwner.expired())
	//		return nullptr;

	//	return m_pOwner.lock()->GetComponent<T>();
	//}
}