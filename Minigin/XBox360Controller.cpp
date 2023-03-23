#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "XBox360Controller.h"

using namespace dae;

class XBox360Controller::XBox360ControllerImpl final
{
	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};

	WORD buttonsPressedThisFrame;
	WORD buttonsReleasedThisFrame;

	int _controllerIndex;

public:
	XBox360ControllerImpl(int controllerIndex)
		:_controllerIndex{ controllerIndex }
	{
		ZeroMemory(&previousState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(_controllerIndex, &currentState);

		auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
		buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
		buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(unsigned int button) const { return buttonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return buttonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return currentState.Gamepad.wButtons & button; }

	glm::vec2 GetLeftThumbStickPos() const { return glm::vec2{ currentState.Gamepad.sThumbLX, currentState.Gamepad.sThumbLY }; }
};



XBox360Controller::XBox360Controller(unsigned int controllerIndex)
	: m_ControllerIndex{ controllerIndex }
{
	pImpl = new XBox360ControllerImpl(controllerIndex);
}

XBox360Controller::~XBox360Controller()
{
	delete pImpl;
}

void XBox360Controller::Update()
{
	pImpl->Update();
}

bool XBox360Controller::IsDown(ControllerButton button) const
{
	return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool XBox360Controller::IsUp(ControllerButton button) const
{
	return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool XBox360Controller::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}

glm::vec2 XBox360Controller::GetLeftThumbStickPos() const
{
	return pImpl->GetLeftThumbStickPos();
}

