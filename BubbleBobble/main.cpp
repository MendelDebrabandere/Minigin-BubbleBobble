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
#include "Minigin.h"

using namespace dae;

int main(int, char* [])
{
	Minigin engine{ "../Data/" };
	BubbleBobble::Create(&engine);
	engine.Run();

	return 0;
}