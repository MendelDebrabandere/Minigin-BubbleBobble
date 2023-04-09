#pragma once
#include <memory>
#include <vector>

#include "TextureComponent.h"
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class Component;

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		void Init();
		void Update();
		void FixedUpdate();
		void Render() const;

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		std::shared_ptr<Transform> GetTransform() const { return m_pTransform; }
		void SetParent(std::shared_ptr<GameObject> pParent);
		std::shared_ptr<GameObject> GetParent() const;
		const std::vector<std::weak_ptr<GameObject>>& GetChildren() const { return m_pChildren; }

		void Destroy();
		bool IsMarkedAsDead() const { return m_IsMarkedDead; };

		template <class T>
		std::shared_ptr<T> AddComponent();

		template <class T>
		bool RemoveComponent();

		template <class T>
		std::shared_ptr<T> GetComponent();

		template <class T>
		bool HasComponent() const;

	private:
		std::weak_ptr<GameObject> m_pParent{};
		std::vector<std::weak_ptr<GameObject>> m_pChildren{};

		std::shared_ptr<Transform> m_pTransform{};
		std::shared_ptr<Texture2D> m_texture{};

		std::vector<std::shared_ptr<Component>> m_Components{};
		std::vector<std::shared_ptr<TextureComponent>> m_pTextures{};

		bool m_IsMarkedDead{};
	};







	template<class T>
	inline std::shared_ptr<T> dae::GameObject::AddComponent()
	{
		static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

		if (HasComponent<T>())
		{
			assert("This component has already been added");
		}

		const auto pComponent{ std::make_shared<T>() };

		pComponent->SetOwner(weak_from_this());

		// Try casting the new component to a RenderComponent, if this succeeds, add this component to the container of render components
		std::shared_ptr<TextureComponent> pAsRenderComponent{ std::dynamic_pointer_cast<TextureComponent>(pComponent) };
		if (pAsRenderComponent)
		{
			m_pTextures.push_back(pAsRenderComponent);
		}

		m_Components.push_back(pComponent);

		return pComponent;
	}

	template <class T>
	inline bool GameObject::RemoveComponent()
	{
		static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

		for (const auto component : m_Components)
		{
			if (std::dynamic_pointer_cast<T>(component))
			{
				delete component;
				return true;
			}
		}
		return false;
	}

	template<class T>
	inline std::shared_ptr<T> dae::GameObject::GetComponent()
	{
		static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

		for (const auto component : m_Components)
		{
			if (std::dynamic_pointer_cast<T>(component))
				return std::dynamic_pointer_cast<T>(component);
		}

		return nullptr;
	}

	template <class T>
	inline bool dae::GameObject::HasComponent() const
	{
		static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

		for (const auto component : m_Components)
		{
			if (std::dynamic_pointer_cast<T>(component))
				return true;
		}
		return false;
	}
}
