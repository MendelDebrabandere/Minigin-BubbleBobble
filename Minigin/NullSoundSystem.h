#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;

		void PlaySound(const std::string&, int, int) override {}
		void PlayMusic(const std::string&, int, int) override {}
		void ToggleMusic(bool /*val*/) override {}

	};
}
