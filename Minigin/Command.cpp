#include "Command.h"

#include <iostream>

#include "InputManager.h"
#include "Time.h"

//The deadzone check happens in the functions themselves
//because then you have the freedom to have function specific deadzones
#define DEADZONEVALUE 0.3

using namespace dae;

void MoveCommand::Execute(unsigned int controllerIdx)
{
	//Get thumbstick pos
	auto pos = InputManager::GetInstance().GetController(controllerIdx)->GetLeftThumbStickPos();

	//Normalize value
	pos /= 32767;

	//Deadzone check (length of thumbstickPos vector < deadzoneSize)
	if (pos.x * pos.x + pos.y * pos.y < DEADZONEVALUE * DEADZONEVALUE)
		return;

	//Add movespeed and make frame independent movement
	constexpr float movespeed{ 100 };
	pos *= Time::GetInstance().GetDelta() * movespeed;

	//Invert y-axis
	pos.y *= -1;

	//Transform GO
	m_pGameObject->GetComponent<Transform>()->Translate(pos.x, pos.y);
}
