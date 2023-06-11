#include "ToggleSoundSysCommand.h"

#include <iostream>
#include <SDL_mixer.h>

#include "SDLSoundSystem.h"
#include "ServiceLocator.h"

void ToggleSoundSysCommand::Execute()
{
	dae::SoundSystem& ss = dae::ServiceLocator::GetSoundSystem();

	if (dynamic_cast<dae::SDLSoundSystem*>(&ss) != nullptr)
	{
		m_SoundIsOn = !m_SoundIsOn;

		if (m_SoundIsOn)
		{
			std::cout << "Unmuted sound\n";
			Mix_Volume(-1, MIX_MAX_VOLUME);
			Mix_VolumeMusic(MIX_MAX_VOLUME);
		}
		else
		{
			Mix_Volume(-1, 0);
			Mix_VolumeMusic(0);
			std::cout << "Muted sound\n";
		}
	}
}
