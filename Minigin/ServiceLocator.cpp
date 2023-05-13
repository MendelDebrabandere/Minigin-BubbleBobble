#include "ServiceLocator.h"

#include "SDLSoundSystem.h"
#include "SoundSystem.h"

using namespace dae;

std::unique_ptr<SoundSystem> ServiceLocator::m_SSInstance = nullptr;

void ServiceLocator::InitDefault()
{
	m_SSInstance = std::make_unique<SDLSoundSystem>();
}

SoundSystem& ServiceLocator::GetSoundSystem()
{
	return *m_SSInstance;
}

void ServiceLocator::RegisterSoundSystem(SoundSystem* ss)
{
	m_SSInstance = std::unique_ptr<SoundSystem>(ss);
}
