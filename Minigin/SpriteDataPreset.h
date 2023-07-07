#pragma once

namespace dae
{
	//This is a preset that can be saved in the class that changes the sprite around
	//So that there is no need to hard code all those values in code and you can store them
	struct SpriteDataPreset
	{
		bool DoOnce;
		int Rows;
		int Columns;
		float AnimTimer;
		int StartIdx;
		int EndIdx;
	};
}