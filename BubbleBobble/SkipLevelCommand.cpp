#include "SkipLevelCommand.h"

#include "SceneSwapper.h"

void SkipLevelCommand::Execute()
{
	SceneSwapper::GetInstance().SkipLevel();
}
