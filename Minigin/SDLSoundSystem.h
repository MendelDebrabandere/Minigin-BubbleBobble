#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override ;
		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&&) = delete;


		void PlaySound(const std::string& fileName, int volume, int loops) override;
		void PlayMusic(const std::string& fileName, int volume, int loops) override;
		void ToggleMusic() override;

	private:
		enum class EventType
		{
			Sound,
			Music
		};

		struct Event
		{
			EventType type;
			std::string fileName;
			int volume;
			int loops;
		};


		class SDL_MixerImpl;
		SDL_MixerImpl* m_pSDL_MixerImpl;
		std::thread m_Thread;
		std::queue<Event> m_EventQueue;
		std::mutex m_QueueMutex;
		std::condition_variable m_ConditionVariable;
		bool m_Quit = false;


		void SoundLoaderThread();
	};
}
