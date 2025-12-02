#include "pch.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "InputManager.h"
#include "Timer.h"
#include "Object.h"
#include "TowerBridge.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"
#define PI 3.14159
#define FPS 60

using json = nlohmann::json;
json j;

// Windows
HWND hWnd = NULL;
bool isFullscreen = false;
RECT windowRect = { 0, 0, 1600, 900 };
RECT fullscreenRect = { 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
MSG msg;
Timer frameTimer = Timer();
InputManager input;
int globalFrameCounter;

// camera
float cameraRotateXAngle = 0.0f;
float cameraRotateYAngle = 0.0f;
float cameraRotateZAngle = 0.0f;
float cameraTransX = -1.0f;
float cameraTransY = 0.0f;
float cameraTransZ = -5.0f;
float gameObjectTransX = 0.0f, gameObjectTransY = 0.0f, gameObjectTransZ = 0.0f;
float gameObjectRotX = 0.0f, gameObjectRotY = 0.0f, gameObjectRotZ = 0.0f;
bool isPerspective = true;
bool isOtho = false;
bool isFrustrum = false;
bool isFirstRun = true;
bool drawAxis = true;

float deltaTime = 0.0f;

TowerBridge towerBridge;
//===================
// JS Practical Test
//===================
float rotation = 0.0f;

HWND GetHWnd() { return hWnd; }

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_F11: {
			if (!GetHWnd()) return 0;
			if (isFullscreen)
			{
				// switch back windows mode
				isFullscreen = false;

				SetWindowLong(GetHWnd(), GWL_STYLE, WS_OVERLAPPEDWINDOW);

				SetWindowPos(GetHWnd(), HWND_NOTOPMOST,
					windowRect.left,
					windowRect.top,
					windowRect.right,
					windowRect.bottom,
					SWP_FRAMECHANGED | SWP_SHOWWINDOW);
			}
			else
			{
				isFullscreen = true;

				SetWindowLong(GetHWnd(), GWL_STYLE, WS_POPUP);

				SetWindowPos(GetHWnd(), HWND_TOP, 0, 0,
					GetSystemMetrics(SM_CXSCREEN),
					GetSystemMetrics(SM_CYSCREEN),
					SWP_FRAMECHANGED | SWP_SHOWWINDOW);
			}
			break;
		}
		case VK_RETURN: {
			towerBridge.ReadData();
			break;
		}
		case VK_UP: {
			cameraTransY -= 0.1f;
			break;
		}
		case VK_DOWN: {
			cameraTransY += 0.1f;
			break;
		}
		case VK_LEFT: {
			cameraTransX += 0.1f;
			break;
		}
		case VK_RIGHT: {
			cameraTransX -= 0.1f;
			break;
		}
		case VK_SPACE: {
			gameObjectRotX = 0;
			gameObjectRotY = 0;
			gameObjectRotZ = 0;
			gameObjectTransX = 0;
			gameObjectTransY = 0;
			gameObjectTransZ = 0;
			cameraTransX = -1.0f;
			cameraTransY = 0;
			cameraTransZ = -5.0f;
			input.SetMouseX(0);
			input.SetMouseY(0);
		}
		case 'X': {
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				cameraRotateXAngle--;
				if (cameraRotateXAngle <= 0.0f)
				{
					cameraRotateXAngle = 360.0f;
				}
			}
			else
			{
				cameraRotateXAngle++;
				if (cameraRotateXAngle >= 360.0f)
				{
					cameraRotateXAngle = 0.0f;
				}
			}
			break;
		}
		case 'Y': {
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				cameraRotateYAngle--;
				if (cameraRotateYAngle <= 0.0f)
				{
					cameraRotateYAngle = 360.0f;
				}
			}
			else
			{
				cameraRotateYAngle++;
				if (cameraRotateYAngle >= 360.0f)
				{
					cameraRotateYAngle = 0.0f;
				}
			}
			break;
		}
		case 'Z': {
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				cameraRotateZAngle--;
				if (cameraRotateZAngle <= 0.0f)
				{
					cameraRotateZAngle = 360.0f;
				}
			}
			else
			{
				cameraRotateZAngle++;
				if (cameraRotateZAngle >= 360.0f)
				{
					cameraRotateZAngle = 0.0f;
				}
			}
			break;
		}
		case 'F': {
			drawAxis = !drawAxis;
			break;
		}
		case 'O': {
			isOtho = true;
			isPerspective = false;
			isFrustrum = false;
			break;
		}
		case 'P': {
			isOtho = false;
			isPerspective = true;
			isFrustrum = false;
			break;
		}
		case 'I': {
			isOtho = false;
			isPerspective = false;
			isFrustrum = true;
			break;
		}
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default: break;
		}
		break;

	case WM_MOUSEMOVE:
	{
		break;
	}

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}
bool ProcessMessages() {
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT)
			return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}
//--------------------------------------------------------------------

bool InitPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void PerspectiveView() {
	float fovy = 50.67f;
	float aspect = 1.777f;
	float nearPerspValue = 0.1f;
	float farPerspValue = 20.0f;
	gluPerspective(fovy, 1600.0f/900.0f, nearPerspValue, farPerspValue);
}

void OrthoView() {
	float left = -2.0f;
	float right = 2.0f;
	float bottom = -2.0f;
	float top = 2.0f;
	float nearValue = -5.0f;
	float farValue = 5.0f;
	glOrtho(left, right, bottom, top, nearValue, farValue);
}

void FrustrumView() {
	float xmin = -1.0f;
	float xmax = 1.0f;
	float ymin = -1.0f;
	float ymax = 1.0f;
	float zmin = 1.0f;
	float zmax = 4.0f;
	glFrustum(xmin, xmax, ymin, ymax, zmin, zmax);
}

void CalcDeltaTime() {
	static auto last = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float>(now - last).count();
	last = now;
}

void UpdateCameraView() {
	glLoadIdentity();
	glTranslatef(gameObjectTransX, gameObjectTransY, gameObjectTransZ);
	glRotatef(gameObjectRotX, 1, 0, 0);
	glRotatef(gameObjectRotY, 0, 1, 0);
	glRotatef(gameObjectRotZ, 0, 0, 1);
}

void DrawAxis() {
	// x axis positive
	glBegin(GL_LINES);
	glColor3f(1.0, 0, 0);
	glPushMatrix();
	glVertex3f(0, 0, 0);
	glVertex3f(20, 0, 0);
	glPopMatrix();
	glEnd();

	// x axis negative
	glBegin(GL_LINES);
	glColor3f(1.0, 0, 1.0);
	glPushMatrix();
	glVertex3f(0, 0, 0);
	glVertex3f(-20, 0, 0);
	glPopMatrix();
	glEnd();

	// y axis positive
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0);
	glPushMatrix();
	glVertex3f(0, 0, 0);
	glVertex3f(0, 20, 0);
	glPopMatrix();
	glEnd();

	// y axis negative
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	glVertex3f(0, 0, 0);
	glVertex3f(0, -20, 0);
	glPopMatrix();
	glEnd();

	// z axis positive
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 20);
	glPopMatrix();
	glEnd();

	// z axis negative
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -20);
	glPopMatrix();
	glEnd();

	// draw point
	
	
	glColor3f(1, 1, 1);
	for (int i= 1; i <= 200; i++) {
		glPointSize(2);
		if (i % 10 == 0) glPointSize(3);
		glBegin(GL_POINTS);
		glVertex3f(i/10.0, 0, 0);
		glVertex3f(0, i/10.0, 0);
		glVertex3f(0, 0, i/10.0);
		glVertex3f(-i/10.0, 0, 0);
		glVertex3f(0, -i/10.0, 0);
		glVertex3f(0, 0, -i/10.0);
	glEnd();
	}
}

void Draw() {
	UpdateCameraView();
	if (drawAxis) DrawAxis();
	towerBridge.Draw(rotation);
}

void Display()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (isPerspective)
	{
		PerspectiveView();
	}
	else if (isOtho)
	{
		OrthoView();
	}
	else if (isFrustrum)
	{
		FrustrumView();
	}
	
	glTranslatef(cameraTransX, cameraTransY, cameraTransZ);
	glRotatef(cameraRotateXAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraRotateYAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(cameraRotateZAngle, 0.0f, 0.0f, 1.0f);

	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glMatrixMode(GL_MODELVIEW);

	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CalcDeltaTime();
	Draw();
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------



void Update(int framesToUpdate) {
	for (int i = 0; i < framesToUpdate; i++) {
		globalFrameCounter++;

		// camera move
		if (input.IsRightMouseDown()) {
			// move front
			if (input.IsKeyPressed(DIK_W)) {
				if (input.IsKeyPressed(DIK_LSHIFT)) cameraTransZ += 0.3;
				else cameraTransZ+= 0.1;
			}
			// move back
			if (input.IsKeyPressed(DIK_S)) {
				if (input.IsKeyPressed(DIK_LSHIFT)) cameraTransZ-= 0.3;
				else cameraTransZ -= 0.1;
			}
			// move left
			if (input.IsKeyPressed(DIK_D)) {
				if (input.IsKeyPressed(DIK_LSHIFT)) cameraTransX-= 0.3;
				else cameraTransX -= 0.1;
			}
			// move right
			if (input.IsKeyPressed(DIK_A)) {
				if (input.IsKeyPressed(DIK_LSHIFT)) cameraTransX+= 0.3;
				else cameraTransX += 0.1;
			}
			// move up
			if (input.IsKeyPressed(DIK_E)) {
				if (input.IsKeyPressed(DIK_LSHIFT)) cameraTransY-= 0.3;
				else cameraTransY -= 0.1;
			}
			// move down
			if (input.IsKeyPressed(DIK_Q)) {
				if (input.IsKeyPressed(DIK_LSHIFT)) cameraTransY+= 0.3;
				else cameraTransY += 0.1;
			}
		}
		if (input.IsKeyPressed(DIK_U) && rotation > -90) {
			rotation--;
		}
		if (input.IsKeyPressed(DIK_P) && rotation < 0) {
			rotation++;
		}
		
			// camera rotation
			gameObjectTransX = -input.GetMouseX()/100.0f;
			gameObjectRotY = input.GetMouseX()/10.0f;
			gameObjectTransY = input.GetMouseY()/100.0f;
			gameObjectRotX = input.GetMouseY()/10.0f;

	}
}

int main(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		windowRect.left, windowRect.top, windowRect.right, windowRect.bottom,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	GetWindowRect(hWnd, &windowRect);

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	InitPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	input.Initialize(hWnd);
	frameTimer.Init(FPS);

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	glEnable(GL_DEPTH_TEST);
	
	ZeroMemory(&msg, sizeof(msg));

	while (ProcessMessages())
	{
		input.Update();
		Update(frameTimer.FramesToUpdate());
		Display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}