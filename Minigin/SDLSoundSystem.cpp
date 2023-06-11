#include "SDLSoundSystem.h"
#include <iostream>
#include <map>
#include <SDL_mixer.h>
#include <SDL.h>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace dae;

class SDLSoundSystem::SDL_MixerImpl final
{
public:
    SDL_MixerImpl()
    {
        Mix_Init(MIX_INIT_MP3);
        SDL_Init(SDL_INIT_AUDIO);
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            printf("SDL_Mixer couldnt init. Err: %s\n", Mix_GetError());
    }
    ~SDL_MixerImpl()
    {
        for (auto& file : m_MusicMap)
        {
            Mix_FreeMusic(file.second);
        }
        for (auto& file : m_SoundsMap)
        {
            Mix_FreeChunk(file.second);
        }
        Mix_Quit();
    }
    SDL_MixerImpl(const SDL_MixerImpl& other) = delete;
    SDL_MixerImpl operator=(const SDL_MixerImpl& rhs) = delete;
    SDL_MixerImpl(SDL_MixerImpl&& other) = delete;
    SDL_MixerImpl operator=(SDL_MixerImpl&& rhs) = delete;

    void PlayMusic(const std::string& fileName, int volume, int loops)
    {
        //Load it first if it hasnt been loaded
        if (m_MusicMap.contains(fileName) == false)
            //Cancel if it cant load it
            if (LoadMusic(fileName) == false)
                return;

        //Volume is a percentage
        volume = (MIX_MAX_VOLUME * volume) / 100;

        //If its not playing anything
        if (Mix_PlayingMusic() == 0)
        {
            Mix_VolumeMusic(volume);
            Mix_PlayMusic(m_MusicMap[fileName], loops);
        }
    }

	void PlaySound(const std::string& fileName, int volume, int loops)
	{
		//Load it first if it hasnt been loaded
		if (m_SoundsMap.contains(fileName) == false)
			//Cancel if it cant load it
			if (LoadSound(fileName) == false)
				return;

		//Volume is a percentage
		volume = (MIX_MAX_VOLUME * volume) / 100;

		//Play it
        Mix_VolumeChunk(m_SoundsMap[fileName], volume);
		Mix_PlayChannel(1, m_SoundsMap[fileName], loops);
	}

    void ToggleMusic()
    {
        if (Mix_PausedMusic() == 1)
        {
            Mix_ResumeMusic();
        }
        else
        {
            Mix_PauseMusic();
        }
    }

private:
	bool LoadMusic(const std::string& fileName)
    {
        Mix_Music* m = nullptr;
        m = Mix_LoadMUS(fileName.c_str());
        if (m == nullptr)
        {
            printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
			return false;
        }
		m_MusicMap.insert(std::make_pair(fileName, m));
		return true;
    }
	bool LoadSound(const std::string& fileName)
    {
        Mix_Chunk* m = nullptr;
        m = Mix_LoadWAV(fileName.c_str());
		if (m == nullptr)
        {
			printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
			return false;
        }
		m_SoundsMap.insert(std::make_pair(fileName,m));
		return true;
    }

    std::map<std::string, Mix_Chunk*> m_SoundsMap;
    std::map<std::string, Mix_Music*> m_MusicMap;
};

SDLSoundSystem::SDLSoundSystem()
    : SoundSystem()
{
    m_pSDL_MixerImpl = new SDL_MixerImpl();
    m_Thread = std::thread(&SDLSoundSystem::SoundLoaderThread, this);
}

SDLSoundSystem::~SDLSoundSystem()
{
    {
        std::lock_guard lock(m_QueueMutex);
        m_Quit = true;
    }
    m_ConditionVariable.notify_all();

    m_Thread.join();

    delete m_pSDL_MixerImpl;
}

void SDLSoundSystem::PlaySound(const std::string& fileName, int volume, int loops)
{
    {
        std::lock_guard lock(m_QueueMutex);
        m_EventQueue.push({ EventType::Sound, fileName, volume, loops });
        //make sure the lock gets unlocked before notifying
    }
    m_ConditionVariable.notify_all();
}

void SDLSoundSystem::PlayMusic(const std::string& fileName, int volume, int loops)
{
    {
        std::lock_guard lock(m_QueueMutex);
        m_EventQueue.push({ EventType::Music, fileName, volume, loops });
        //make sure the lock gets unlocked before notifying
    }
    m_ConditionVariable.notify_all();
}

void SDLSoundSystem::ToggleMusic()
{
    m_pSDL_MixerImpl->ToggleMusic();
}

void SDLSoundSystem::SoundLoaderThread()
{
    while (true)
    {
        //Acquire a lock
        std::unique_lock lock(m_QueueMutex);

        //This unlocks the lock and makes the thread sleep untill it gets notified
        //If notified, it checks the lambda to see if it can continue
        //If it can continue it locks the lock again
        m_ConditionVariable.wait(lock, [this] { return !m_EventQueue.empty() || m_Quit; });

        if (m_Quit)
            break;

        Event event = m_EventQueue.front();
        m_EventQueue.pop();
        lock.unlock();

        if (event.type == EventType::Sound)
        {
            m_pSDL_MixerImpl->PlaySound(event.fileName, event.volume, event.loops);
        }
        else if (event.type == EventType::Music)
        {
            m_pSDL_MixerImpl->PlayMusic(event.fileName, event.volume, event.loops);
        }
    }
}
