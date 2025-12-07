#include "pch.h"
#include "InputManager.h"

InputManager::InputManager() {
	dInput = nullptr;
	dInputKeyboardDevice = nullptr;
	dInputMouseDevice = nullptr;
	ZeroMemory(&mouseState, sizeof(mouseState));
	ZeroMemory(diKeys, sizeof(diKeys));
	currentXpos = 0;
	currentYpos = 0;
}

InputManager::~InputManager() {
	CleanUp();
}

bool InputManager::Initialize(HWND hwnd) {
	HRESULT hr;

	// Create the Direct Input object.
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
	if (FAILED(hr)) return false;

	// Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	if (FAILED(hr)) return false;
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	dInputKeyboardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputKeyboardDevice->Acquire();

	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	if (FAILED(hr)) return false;
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	dInputMouseDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputMouseDevice->Acquire();

	return true;
}

void InputManager::Update() {
	
	if (FAILED(dInputKeyboardDevice->GetDeviceState(256, diKeys))) {
		dInputKeyboardDevice->Acquire();
	}

	if (FAILED(dInputMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState))) {
		dInputMouseDevice->Acquire(); // re-acquire if focus lost
		ZeroMemory(&mouseState, sizeof(mouseState));
	}

	currentXpos += mouseState.lX;
	currentYpos += mouseState.lY;
	mouseScroll = mouseState.lZ;
}

bool InputManager::IsKeyPressed(BYTE key) {
	return diKeys[key] & 0x80;
}

bool InputManager::IsLeftMouseDown() {
	return (mouseState.rgbButtons[0] & 0x80) != 0;
}

bool InputManager::IsRightMouseDown() {
	return (mouseState.rgbButtons[1] & 0x80) != 0;
}

LONG InputManager::GetMouseX() {
	return currentXpos;
}

void InputManager::SetMouseX(LONG x)
{
	currentXpos = x;
}

LONG InputManager::GetMouseY() {
	return currentYpos;
}

void InputManager::SetMouseY(LONG y)
{
	currentYpos = y;
}

float InputManager::GetMouseScroll()
{
	return mouseState.lZ;
}

void InputManager::CleanUp() {
	// Release keyboard device.
	if (dInputKeyboardDevice) {
		dInputKeyboardDevice->Unacquire();
		dInputKeyboardDevice->Release();
		dInputKeyboardDevice = nullptr;
	}

	if (dInputMouseDevice) {
		dInputMouseDevice->Unacquire();
		dInputMouseDevice->Release();
		dInputMouseDevice = nullptr;
	}

	if (dInput) {
		// Release DirectInput.
		dInput->Release();
		dInput = nullptr;
	}
}