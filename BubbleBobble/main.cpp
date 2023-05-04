#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

//#include "Minigin.h"
//
//int main(int, char* []) {
//	dae::Minigin engine;
//	engine.Run();
//
//	return 0;
//}

#include "BubbleBobble.h"
#include "FPSCounter.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "HealthComponent.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"

using namespace dae;

int main(int, char* [])
{
	Minigin engine{ "../Data/" };
	BubbleBobble::Create(&engine);
	engine.Run();

	return 0;
}