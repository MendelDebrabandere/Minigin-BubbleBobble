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
	for (size_t  i = 0; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i]->GetName() == name)
		{
			m_ActiveSceneIdx = static_cast<int>(i);
		}
	}
}

void SceneManager::SetActiveScene(const Scene* pScene)
{
	for (size_t i = 0; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i].get() == pScene)
			m_ActiveSceneIdx = static_cast<int>(i);
	}
}

Scene* SceneManager::GetActiveScene() const
{
	if (m_Scenes.size() != 0 && m_ActiveSceneIdx != -1)
		return m_Scenes[m_ActiveSceneIdx].get();
	else
		return nullptr;
}


void SceneManager::FixedUpdate()
{
	if (m_ActiveSceneIdx >= 0)
	{
		m_Scenes[m_ActiveSceneIdx]->FixedUpdate();
	}
}

void SceneManager::Update()
{
	if (m_ActiveSceneIdx >= 0)
	{
		m_Scenes[m_ActiveSceneIdx]->Update();
	}
}

void SceneManager::Render() const
{
	if (m_ActiveSceneIdx >= 0)
	{
		m_Scenes[m_ActiveSceneIdx]->Render();
	}
}

void SceneManager::UpdateCleanup()
{
	if (m_ActiveSceneIdx >= 0)
	{
		m_Scenes[m_ActiveSceneIdx]->UpdateCleanup();
	}
}

