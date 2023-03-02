#pragma once
#include <memory>
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class Component;

	// todo: this should become final.
	class GameObject 
	{
	public:
		virtual void Update();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <class T>
		void AddComponent() { m_Component = new T(); }

		bool RemoveComponent();

		template <class T>
		T GetComponent() { return m_Component; }

		bool HasComponent() const;

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};

		Component* m_Component{ nullptr };
	};
}
