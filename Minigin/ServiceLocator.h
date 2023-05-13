#pragma once
#include <algorithm>
#include <memory>


namespace dae
{
	class SoundSystem;

	class ServiceLocator final
	{
	public:
		ServiceLocator() = default;
		~ServiceLocator() = default;
		ServiceLocator(const ServiceLocator&) = delete;
		ServiceLocator(ServiceLocator&&) = delete;
		ServiceLocator& operator=(const ServiceLocator&) = delete;
		ServiceLocator& operator=(ServiceLocator&&) = delete;

		static void InitDefault();
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(SoundSystem* ss);

	private:
		static std::unique_ptr<SoundSystem> m_SSInstance;
	};

}

