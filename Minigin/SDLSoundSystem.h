#pragma once
#include <memory>

#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem final : public SoundSystem 
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();

		void PlaySound(const std::string& fileName, int volume, bool loop) override;
		void PlayMusic(const std::string& fileName, int volume, bool loop) override;
		void ToggleMusic() override;

	private:
		class SDL_MixerImpl;
		SDL_MixerImpl* m_pSDL_MixerImpl;
	};
}
