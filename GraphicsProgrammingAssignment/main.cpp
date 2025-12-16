#include "pch.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "InputManager.h"
#include "Timer.h"
#include "Object.h"
#include "TowerBridge.h"
#include "Light.h"
#include "Tetrahedron.h"
#include "BackBone.h"
#include "FrustumCube.h"

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

// light
GLUquadricObj* var = gluNewQuadric();
Light light0 = Light( { 0.2f, 0.2f, 0.2f, 1.0f}, { 1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, GL_LIGHT0);
Cube c1 = Cube(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
Pyramid p1 = Pyramid(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
Tetrahedron t1 = Tetrahedron(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
Cylinder cylinder1 = Cylinder(1.0f, 1.0f, 1.0f, 50, 50, GLU_FILL, true, 1.0f, 1.0f, 1.0f, 1.0f);
Sphere sphere1 = Sphere(1.0f, 10, 10, GLU_FILL, 1.0f, 1.0f, 1.0f, 1.0f);
FrustumCube frustumCube = FrustumCube(0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
// Textures
GLuint tex1 = 0;
BITMAP BMP;
HBITMAP hBMP;

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

// TowerBridge towerBridge;
Object background("background.json");
BackBone backbone;

float camPosX = 0.0f, camPosY = 0.0f, camPosZ = 5.0f;
float camYaw = 0.0f;   // Y-axis rotation (left/right)
float camPitch = 0.0f; // X-axis rotation (up/down)

float x = 0, y = 0, z = 0;

HWND GetHWnd() { return hWnd; }

void ReadData() {
	background.ReadData();
	backbone.ReadData();
	//towerBridge.ReadData();
}

void LoadTexture(LPCSTR filename, GLuint& texID, bool isRepeat)
{
	if (texID != 0) {
		std::cout << "Tex ID error" << std::endl;
		return;
	}

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if (!hBMP) {
		std::cout << "hBmp error" << std::endl;
		return;
	}

	GetObject(hBMP, sizeof(BITMAP), &BMP);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	// optionally set wrapping
	if (isRepeat) {
		// X axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		// Y axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
}

void ClearTexture() {
	glDeleteTextures(1, &tex1);
	DeleteObject(hBMP);
}

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
			ReadData();
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
			break;
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
		/*case 'J': {
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				light0->Move(light0->GetPosition()[0] - 0.1f, light0->GetPosition()[1], light0->GetPosition()[2]);
			}
			else
			{
				light0->Move(light0->GetPosition()[0] + 0.1f, light0->GetPosition()[1], light0->GetPosition()[2]);
			}
			break;
		}
		case 'K': {
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				light0->Move(light0->GetPosition()[0], light0->GetPosition()[1] - 0.1f, light0->GetPosition()[2]);
			}
			else
			{
				light0->Move(light0->GetPosition()[0], light0->GetPosition()[1] + 0.1f, light0->GetPosition()[2]);
			}
			break;
		}
		case 'L': {
			if (GetKeyState(VK_SHIFT) & 0x8000)
			{
				light0->Move(light0->GetPosition()[0], light0->GetPosition()[1] , light0->GetPosition()[2] - 0.1f);
			}
			else
			{
				light0->Move(light0->GetPosition()[0], light0->GetPosition()[1], light0->GetPosition()[2] + 0.1f);
			}
			break;
		}*/
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
	float farPerspValue = 40.0f;
	gluPerspective(fovy, 1600.0f/900.0f, nearPerspValue, farPerspValue);
}

void OrthoView() {
	float left = -10.0f;
	float right = 10.0f;
	float bottom = -10.0f;
	float top = 10.0f;
	float nearValue = -10.0f;
	float farValue = 50.0f;
	glOrtho(left, right, bottom, top, nearValue, farValue);
}

void FrustrumView() {
	float xmin = -0.1f;
	float xmax = 0.1f;
	float ymin = -0.1f;
	float ymax = 0.1f;
	float zmin = 0.1f;
	float zmax = 40.0f;

	glFrustum(xmin, xmax, ymin, ymax, zmin, zmax);
}

void CalcDeltaTime() {
	static auto last = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float>(now - last).count();
	last = now;
}

void UpdateCameraView() {
	glRotatef(-camPitch, 1, 0, 0);
	glRotatef(-camYaw, 0, 1, 0);
	glTranslatef(-camPosX, -camPosY, -camPosZ);
}

void DrawAxis() {
	glDisable(GL_LIGHTING);
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
	glEnable(GL_LIGHTING);
}

void Draw() {
	glPushMatrix();
	if (drawAxis) DrawAxis();
	backbone.RotateLeftFoot(x, y, z);
	//towerBridge.Draw(0);
	//backbone.RotateHead(x, y, z);
	backbone.RotateRightForearm(0, -90);
	backbone.RotateLeftForearm(0, -90);
	//backbone.RotateRightHandFinger(90, 90, 90);
	backbone.RotateLeftHandFinger(x, y, z);
	backbone.Draw();

	glPushMatrix();
	glTranslatef(light0.GetPosition()[0], light0.GetPosition()[1], light0.GetPosition()[2]);
	GLfloat redColor[] = { 1.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, redColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redColor);
	gluSphere(var, 0.1f, 10.0f, 10.0f);
	glPopMatrix();

	c1.Translate(-10.0f, 0.0f, 10.0f);
	c1.Draw();
	p1.Translate(-5.0f, 0.0f, 10.0f);
	p1.Draw();
	t1.Translate(-15.0f, 0.0f, 10.0f);
	t1.Draw();
	cylinder1.Translate(-20.0f, 0.0f, 10.0f);
	cylinder1.Draw();
	sphere1.Translate(0.0f, 0.0f, 10.0f);
	sphere1.Draw();
	frustumCube.Translate(5.0f, 0.0f, 10.0f);
	frustumCube.Draw();
	
	glPopMatrix();
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

	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	background.Draw();
	glEnable(GL_LIGHTING);
	UpdateCameraView();
	glTranslatef(cameraTransX, cameraTransY, cameraTransZ);
	glRotatef(cameraRotateXAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraRotateYAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(cameraRotateZAngle, 0.0f, 0.0f, 1.0f);

	light0.Update();

	
	

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
		float speed = input.IsKeyPressed(DIK_LSHIFT) ? 0.3f : 0.1f;

		float forwardX = sinf(camYaw * PI / 180);
		float forwardZ = cosf(camYaw * PI / 180);

		float rightX = cosf(camYaw * PI / 180);
		float rightZ = -sinf(camYaw * PI / 180);

		// Move Forward/Back
		if (input.IsKeyPressed(DIK_S))
			camPosX += forwardX * speed,
			camPosZ += forwardZ * speed;

		if (input.IsKeyPressed(DIK_W))
			camPosX -= forwardX * speed,
		camPosZ -= forwardZ * speed;

		// Move Left/Right
		if (input.IsKeyPressed(DIK_A))
			camPosX -= rightX * speed,
			camPosZ -= rightZ * speed;

		if (input.IsKeyPressed(DIK_D))
			camPosX += rightX * speed,
			camPosZ += rightZ * speed;

		// camera rotation
		camYaw -= input.GetMouseX() * 0.1f;
		camPitch -= input.GetMouseY() * 0.1f;

		// Clamp pitch
		if (camPitch > 89.0f)  camPitch = 89.0f;
		if (camPitch < -89.0f) camPitch = -89.0f;

		input.SetMouseX(0);
		input.SetMouseY(0);

		// Move Up/Down
		if (input.IsKeyPressed(DIK_E)) {
			camPosY += speed;
		}
		if (input.IsKeyPressed(DIK_Q)) {
			camPosY -= speed;
		}

		// Light move
		// x direction
		if (input.IsKeyPressed(DIK_J))
		{
			if (input.IsKeyPressed(DIK_LSHIFT))
			{
				light0.Move(light0.GetPosition()[0] - 0.1f, light0.GetPosition()[1], light0.GetPosition()[2]);
			}
			else {
				light0.Move(light0.GetPosition()[0] + 0.1f, light0.GetPosition()[1], light0.GetPosition()[2]);
			}
		}

		// y direction
		if (input.IsKeyPressed(DIK_K))
		{
			if (input.IsKeyPressed(DIK_LSHIFT))
			{
				light0.Move(light0.GetPosition()[0], light0.GetPosition()[1] - 0.1f, light0.GetPosition()[2]);
			}
			else {
				light0.Move(light0.GetPosition()[0], light0.GetPosition()[1] + 0.1f, light0.GetPosition()[2]);
			}
		}

		// z direction
		if (input.IsKeyPressed(DIK_L))
		{
			if (input.IsKeyPressed(DIK_LSHIFT))
			{
				light0.Move(light0.GetPosition()[0], light0.GetPosition()[1], light0.GetPosition()[2] - 0.1f);
			}
			else {
				light0.Move(light0.GetPosition()[0], light0.GetPosition()[1], light0.GetPosition()[2] + 0.1f);
			}
			
		}

		//=======================
		// Testing key
		//=======================
		if (input.IsKeyPressed(DIKEYBOARD_NUMPAD1))
		{
			if (input.IsKeyPressed(DIK_LSHIFT))
			{
				x--;
			}
			else {
				x++;
			}

		}
		if (input.IsKeyPressed(DIKEYBOARD_NUMPAD2))
		{
			if (input.IsKeyPressed(DIK_LSHIFT))
			{
				y--;
			}
			else {
				y++;
			}

		}
		if (input.IsKeyPressed(DIKEYBOARD_NUMPAD3))
		{
			if (input.IsKeyPressed(DIK_LSHIFT))
			{
				z--;
			}
			else {
				z++;
			}

		}
		if (input.IsKeyPressed(DIKEYBOARD_NUMPAD8)) {
			backbone.RotateRightIndex(0, 0, 0);
		}
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
	light0.Enable();
	glEnable(GL_LIGHTING);
	gluQuadricTexture(var, GL_TRUE);
	gluQuadricNormals(var, GLU_SMOOTH);
	glEnable(GL_TEXTURE_2D);

	// let texture can response with light
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_NORMALIZE);
	
	LoadTexture("Assets/meme1.bmp", tex1, true);
	c1.SetAllTextures(tex1);
	p1.SetAllTextures(tex1);
	t1.SetAllTextures(tex1);
	cylinder1.SetAllTextures(tex1);
	sphere1.SetSphereTexture(tex1);
	frustumCube.SetAllTextures(tex1);

	ZeroMemory(&msg, sizeof(msg));

	backbone.SetBone();

	while (ProcessMessages())
	{
		input.Update();
		Update(frameTimer.FramesToUpdate());
		Display();
		SwapBuffers(hdc);
	}
	gluDeleteQuadric(var);

	ClearTexture();

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
