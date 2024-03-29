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

		Scene* GetActiveScene() const;

		void FixedUpdate();
		void Update();
		void Render() const;
		void UpdateCleanup();

	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_ActiveSceneIdx{-1};
	};
}
