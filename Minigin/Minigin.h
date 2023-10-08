#pragma once
#include <functional>
#include <mutex>
#include <queue>
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

		static void LockMutex() { s_Mutex.lock(); }
		static void UnlockMutex() { s_Mutex.unlock(); }

		static void AddTask(const std::function<void()> func) { s_Tasks.push(func); }
	private:
		SceneManager* mpSceneManager;


		inline static std::mutex s_Mutex{};
		inline static std::queue<std::function<void()>> s_Tasks{};
	};
}