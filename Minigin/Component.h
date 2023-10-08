#pragma once
#include <document.h>

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

		virtual void Initialize() {}
		virtual void Render() const {}
		virtual void FixedUpdate() {}
		virtual void Update() {}

		GameObject* GetOwner() const;
		void SetOwner(GameObject* pParent);

		virtual rapidjson::Value Serialize(rapidjson::Document::AllocatorType& /*allocator*/) const { return {}; }
		virtual void Deserialize(const rapidjson::Value& /*value*/) {}

	protected:
		GameObject* m_pOwner{};
	};
}
