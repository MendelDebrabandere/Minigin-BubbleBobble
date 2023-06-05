#pragma once
#include <functional>
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

		Scene* GetActiveScene();

		void FixedUpdate();
		void Update();
		void Render();
		void UpdateCleanup();

		void SetSceneSelector(std::function<void()> sceneSelectorFunction);

	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_ActiveSceneIdx{-1};

		std::function<void()> m_SceneSelectorFunction;
	};
}
