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

		virtual void Render() const {}

		virtual void Update() {}
		virtual void FixedUpdate() {}

		GameObject* GetOwner() const;
		void SetOwner(GameObject* pParent);

	protected:
		GameObject* m_pOwner{};
	};
}