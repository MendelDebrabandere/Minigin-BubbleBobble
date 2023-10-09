#include "Scene.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

GameObject* Scene::CreateGameObject()
{
	auto pGameObject{ std::make_unique<GameObject>() };
	pGameObject->Init();

	GameObject* pGameObjectPtr{ pGameObject.get() };

	Add(std::move(pGameObject));
	return pGameObjectPtr;
}

void Scene::FixedUpdate()
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::UpdateCleanup()
{
	// Remove gameobjects from their container if they are marked as dead
	m_objects.erase(std::remove_if(begin(m_objects), end(m_objects), [](const auto& pGameObject)
		{
			return pGameObject->IsMarkedAsDead();
		}), end(m_objects));
}

const std::string& Scene::GetName() const
{
	return m_name;
}

void Scene::SetName(const std::string& name)
{
	m_name = name;
}

rapidjson::Document Scene::SerializeScene() const
{
	rapidjson::Document doc;
	doc.SetObject();

	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

	// Serialize scene name
	doc.AddMember("name", rapidjson::Value(m_name.c_str(), allocator), allocator);

	// Serialize game objects
	rapidjson::Value objects(rapidjson::kArrayType);
	for (const auto& object : m_objects)
	{
		if (object->IsMarkedAsDead() == false)
			objects.PushBack(object->Serialize(allocator), allocator);
	}
	doc.AddMember("objects", objects, allocator);

	return doc;
}

void Scene::Deserialize(const rapidjson::Document& doc)
{
	//TODO: Assuming the Scene name is not changed during runtime and does not need deserialization

	// Deserialize all game objects
	const rapidjson::Value& objects = doc["objects"];
	assert(objects.IsArray());


	auto& allObj = GetAllObjects();

	std::vector<int> objIds{};

	for (const auto& jsonObj : objects.GetArray())
	{
		if ((jsonObj.HasMember("id") && jsonObj["id"].IsInt()) == false)
			continue;

		objIds.push_back(jsonObj["id"].GetInt());

		bool foundObj{ false };
		for (const auto& gameObj : allObj)
		{
			if (gameObj->GetId() == jsonObj["id"].GetInt() && gameObj->IsMarkedAsDead() == false)
			{
				foundObj = true;
				gameObj->Deserialize(jsonObj);
				break;
			}
		}

		if (foundObj == false)
		{
			//TODO: MAKE THE OBJ
		}

	}

	
	// - Deleting game objects that exist in the current scene but not in the received data
	for (const auto& gameObj : allObj)
	{
		bool foundObj{ false };
		for (const auto& jsonObj : objects.GetArray())
		{
			if ((jsonObj.HasMember("id") && jsonObj["id"].IsInt()) == false)
				continue;

			if (gameObj->GetId() == jsonObj["id"].GetInt())
			{
				foundObj = true;
				break;
			}
		}
		if (foundObj == false)
		{
			gameObj->Destroy();
		}
	}
}