#include "SceneManager.h"
#include "Scene.h"

using namespace dae;

Scene* SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::make_shared<Scene>(name);
	m_Scenes.push_back(scene);
	return scene.get();
}

void SceneManager::SetActiveScene(const std::string& name)
{
	for (unsigned int i = 0; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i]->GetName() == name)
			m_ActiveSceneIdx = i;
	}
}

void SceneManager::SetActiveScene(const Scene* pScene)
{
	for (unsigned int i = 0; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i].get() == pScene)
			m_ActiveSceneIdx = i;
	}
}

Scene* SceneManager::GetActiveScene()
{
	if (m_Scenes.size() != 0 && m_ActiveSceneIdx != -1)
		return m_Scenes[m_ActiveSceneIdx].get();
	else
		return nullptr;
}


void SceneManager::FixedUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate();
	}
}

void SceneManager::Update()
{
	if (m_SceneSelectorFunction)
		m_SceneSelectorFunction();

	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void SceneManager::UpdateCleanup()
{
	for (auto& scene : m_Scenes)
	{
		scene->UpdateCleanup();
	}
}

void SceneManager::SetSceneSelector(std::function<void()> sceneSelectorFunction)
{
	m_SceneSelectorFunction = sceneSelectorFunction;
}

