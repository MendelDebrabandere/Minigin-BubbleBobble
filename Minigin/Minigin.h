#pragma once
#include <functional>

namespace dae
{
	class SceneManager;

	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		SceneManager* GetSceneManager();

		void Run();

	private:
		SceneManager* mpSceneManager;
	};
}