#pragma once
#include <string>

namespace dae
{
	class SceneManager;

	class Minigin final
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		SceneManager* GetSceneManager() const;

		void Run();

	private:
		SceneManager* mpSceneManager;
	};
}