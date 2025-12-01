#include "pch.h"

class InputManager {
private:
	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
	LPDIRECTINPUTDEVICE8 dInputMouseDevice;
	DIMOUSESTATE mouseState;
	BYTE diKeys[256];
	LONG currentXpos;
	LONG currentYpos;
	LONG windowHeight = 720;
	LONG windowWidth = 1080;
public:
	InputManager();
	~InputManager();

	bool Initialize(HWND hwnd);
	void Update();
	bool IsKeyPressed(BYTE key);
	LONG GetMouseX();
	void SetMouseX(LONG x);
	LONG GetMouseY();
	void SetMouseY(LONG y);
	void CleanUp();
	bool IsLeftMouseDown();
	bool IsRightMouseDown();
	void SetWindowHeight(int h) { windowHeight = h; }
	void SetWindowWidth(int w) { windowWidth = w; }
	LONG GetWindowWidth() { return windowWidth; }
	LONG GetWindowHeight() { return windowHeight; }
};