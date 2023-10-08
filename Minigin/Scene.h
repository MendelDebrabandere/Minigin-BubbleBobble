#pragma once
#include <document.h>

#include "GameObject.h"

namespace dae
{
	class Scene final
	{
	public:
		explicit Scene(const std::string& name);

		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		GameObject* CreateGameObject();

		void FixedUpdate();
		void Update();
		void Render() const;

		void UpdateCleanup();

		const std::string& GetName() const;
		void SetName(const std::string& name);

		std::vector<std::unique_ptr<GameObject>>& GetAllObjects() { return m_objects; }

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		rapidjson::Document SerializeScene() const;
		void Deserialize(const rapidjson::Document& doc);


	private: 

		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter; 
	};

}
