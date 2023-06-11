#pragma once
#include <string>
namespace dae
{
	class SoundSystem
	{
	public:
		SoundSystem() = default;
		virtual ~SoundSystem() = default;
		SoundSystem(const SoundSystem&) = delete;
		SoundSystem(SoundSystem&&) = delete;
		SoundSystem& operator=(const SoundSystem&) = delete;
		SoundSystem& operator=(SoundSystem&&) = delete;

		virtual void PlaySound(const std::string& fileName, int volume, int loops) = 0;
		virtual void PlayMusic(const std::string& fileName, int volume, int loops) = 0;
		virtual void ToggleMusic(bool val) = 0;
	};
}

