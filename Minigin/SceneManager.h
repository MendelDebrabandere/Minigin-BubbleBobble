#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		SceneManager() = default;

		Scene* CreateScene(const std::string& name);
		void SetActiveScene(const std::string& name);
		void SetActiveScene(const Scene* pScene);

		void Update();
		void Render();
		void FixedUpdate();
		void UpdateCleanup();
	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_ActiveSceneIdx{-1};
	};
}
