#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BubbleBobble.h"
#include "Minigin.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"

using namespace dae;

int main(int, char* [])
{
	// Register the soundSystem
	ServiceLocator::InitDefault();

	Minigin engine{ std::string("../Data/") };
	BubbleBobble::Create();
	engine.Run();

	return 0;
}