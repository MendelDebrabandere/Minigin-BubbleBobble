#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"

#include <chrono>

#include "EventQueue.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "ServerConnector.h"

using namespace dae;

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version;
	SDL_VERSION(&version)
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version)
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 exam: Bubble Bobble | Mendel Debrabandere 2DAE07",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280,
		800,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	m_RandomSeed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
	std::srand(m_RandomSeed);

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);

	Time::GetInstance().Init();

	mpSceneManager = &SceneManager::GetInstance();

	ServerConnector::GetInstance().Init();
}

Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

SceneManager* Minigin::GetSceneManager() const
{
	return mpSceneManager;
}

void Minigin::Run()
{
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = Time::GetInstance();
	auto& events = EventQueue::GetInstance();

	bool doContinue = true;
	constexpr float fixedTimeStep{ 0.005f }; // 200 times per second
	constexpr float maxFrameTime{ 0.01f }; // cap fps at 100
	float lag{};
	time.SetFixedTimeStep(fixedTimeStep);

	while (doContinue)
	{
		const auto frameStart{ std::chrono::high_resolution_clock::now() };

		//use a mutex so that the multiplayer thread wont interfere during gameplay
		LockMutex();

		//do all tasks for the main thread now (other threads give tasks to main thread)
		while (!s_Tasks.empty())
		{
			s_Tasks.front()();
			s_Tasks.pop();
		}

		time.Update();
		lag += time.GetDelta();

		doContinue = input.ProcessInput();

		while (lag >= fixedTimeStep)
		{
			sceneManager.FixedUpdate();
			sceneManager.UpdateCleanup();
			lag -= fixedTimeStep;
		}

		sceneManager.Update();

		events.NotifyListeners();

		sceneManager.UpdateCleanup();

		renderer.Render();

		ResourceManager::GetInstance().CheckForDeletedTextures();

		UnlockMutex();

		const float frameTime{ std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - frameStart).count() };
		const float sleepTime{ maxFrameTime - frameTime };
		// CAP FPS IF NEEDED
		if (sleepTime > 0.f)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<LONGLONG>(sleepTime * 1000)));
		}
	}
}
