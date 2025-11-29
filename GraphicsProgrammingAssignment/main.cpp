#include "pch.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Cylinder.h"
#include "Sphere.h"

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"
#define PI 3.14159

using json = nlohmann::json;
json j;

// Windows
HWND hWnd = NULL;
bool isFullscreen = false;
RECT windowRect = { 0, 0, 1600, 900 };
RECT fullscreenRect = { 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };

// camera
float cameraRotateXAngle = 0.0f;
float cameraRotateYAngle = 0.0f;
float cameraRotateZAngle = 0.0f;
float cameraTransX = -1.0f;
float cameraTransY = 0.0f;
float cameraTransZ = -5.0f;
bool isPerspective = true;
bool isOtho = true;
bool isFrustrum = true;
bool isFirstRun = true;

float deltaTime = 0.0f;

HWND GetHWnd() { return hWnd; }

struct CylinderData {
	float baseRadius;
	float topRadius;
	float height;
	int slices;
	int stacks;
	GLenum style;
	bool isClose;
	float lineWidth;
	float r;
	float g;
	float b;
	float transX;
	float transY;
	float transZ;
	float rotX;
	float rotY;
	float rotZ;
	float scaleX;
	float scaleY;
	float scaleZ;
};

struct SphereData {
	float radius;
	int slices;
	int stacks;
	GLenum style;
	float lineWidth;
	float r;
	float g;
	float b;
	float transX;
	float transY;
	float transZ;
	float rotX;
	float rotY;
	float rotZ;
	float scaleX;
	float scaleY;
	float scaleZ;
};

struct CubeData {
	float length;
	float width;
	float height;
	float r;
	float g;
	float b;
	float transX;
	float transY;
	float transZ;
	float rotX;
	float rotY;
	float rotZ;
	float scaleX;
	float scaleY;
	float scaleZ;
};

struct PyramidData {
	float length;
	float width;
	float height;
	float r;
	float g;
	float b;
	float transX;
	float transY;
	float transZ;
	float rotX;
	float rotY;
	float rotZ;
	float scaleX;
	float scaleY;
	float scaleZ;
};

std::vector<CylinderData> cylindersData;
std::vector<SphereData> spheresData;
std::vector<CubeData> cubesData;
std::vector<PyramidData> pyramidsData;

std::vector<std::unique_ptr<Cylinder>> cylinders;
std::vector<std::unique_ptr<Sphere>> spheres;
std::vector<std::unique_ptr<Cube>> cubes;
std::vector<std::unique_ptr<Pyramid>> pyramids;

void DrawRobot();
void ReadData();

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
		case 'S': {
			cameraTransZ -= 0.1f;
			break;
		}
		case 'W': {
			cameraTransZ += 0.1f;
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
	float farPerspValue = 10.0f;
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
	DrawRobot();

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

void DrawRobot() {
	glLoadIdentity();

	for (auto& cylinder : cylinders)
	{
		cylinder->Draw();
	}

	for (auto& sphere : spheres)
	{
		sphere->Draw();
	}

	for (auto& cube : cubes)
	{
		cube->Draw();
	}

	for (auto& pyramid : pyramids)
	{
		pyramid->Draw();
	}
}

void ReadData() {
	
	glLoadIdentity();

	cylindersData.clear();
	spheresData.clear();
	cubesData.clear();
	pyramidsData.clear();

	// open json file
	std::ifstream file("data.json");

	if (!file.is_open()) {
		std::cout << "Failed to open JSON file!" << std::endl;
		return;
	}

	try {
		file >> j;
	}
	catch (nlohmann::json::parse_error& e) {
		std::cout << "JSON parse error: " << e.what() << std::endl;
		return;
	}

	for (auto& jc : j["cylinders"]) {
		CylinderData c;
		c.baseRadius = jc["baseRadius"];
		c.topRadius = jc["topRadius"];
		c.height = jc["height"];
		c.slices = jc["slices"];
		c.stacks = jc["stacks"];
		if (jc["style"] == "GLU_LINE")
		{
			c.style = GLU_LINE;
		}
		else if (jc["style"] == "GLU_FILL")
		{
			c.style = GLU_FILL;
		}
		c.isClose = jc["isClose"];
		c.lineWidth = jc["lineWidth"];
		c.r = jc["r"];
		c.g = jc["g"];
		c.b = jc["b"];

		c.transX = jc["transX"];
		c.transY = jc["transY"];
		c.transZ = jc["transZ"];

		c.rotX = jc["rotX"];
		c.rotY = jc["rotY"];
		c.rotZ = jc["rotZ"];

		c.scaleX = jc["scaleX"];
		c.scaleY = jc["scaleY"];
		c.scaleZ = jc["scaleZ"];

		cylindersData.push_back(c);
	}

	for (auto& jc : j["spheres"]) {
		SphereData s;
		s.radius = jc["radius"];
		s.slices = jc["slices"];
		s.stacks = jc["stacks"];
		if (jc["style"] == "GLU_LINE")
		{
			s.style = GLU_LINE;
		}
		else if (jc["style"] == "GLU_FILL")
		{
			s.style = GLU_FILL;
		}
		s.lineWidth = jc["lineWidth"];
		s.r = jc["r"];
		s.g = jc["g"];
		s.b = jc["b"];

		s.transX = jc["transX"];
		s.transY = jc["transY"];
		s.transZ = jc["transZ"];

		s.rotX = jc["rotX"];
		s.rotY = jc["rotY"];
		s.rotZ = jc["rotZ"];

		s.scaleX = jc["scaleX"];
		s.scaleY = jc["scaleY"];
		s.scaleZ = jc["scaleZ"];

		spheresData.push_back(s);
	}

	for (auto& jc : j["cubes"]) {
		CubeData c;
		c.length = jc["length"];
		c.width = jc["width"];
		c.height = jc["height"];
		c.r = jc["r"];
		c.g = jc["g"];
		c.b = jc["b"];

		c.transX = jc["transX"];
		c.transY = jc["transY"];
		c.transZ = jc["transZ"];

		c.rotX = jc["rotX"];
		c.rotY = jc["rotY"];
		c.rotZ = jc["rotZ"];

		c.scaleX = jc["scaleX"];
		c.scaleY = jc["scaleY"];
		c.scaleZ = jc["scaleZ"];

		cubesData.push_back(c);
	}

	for (auto& jc : j["pyramids"]) {
		PyramidData p;
		p.length = jc["length"];
		p.width = jc["width"];
		p.height = jc["height"];
		p.r = jc["r"];
		p.g = jc["g"];
		p.b = jc["b"];

		p.transX = jc["transX"];
		p.transY = jc["transY"];
		p.transZ = jc["transZ"];

		p.rotX = jc["rotX"];
		p.rotY = jc["rotY"];
		p.rotZ = jc["rotZ"];

		p.scaleX = jc["scaleX"];
		p.scaleY = jc["scaleY"];
		p.scaleZ = jc["scaleZ"];

		pyramidsData.push_back(p);
	}

	// When start program
	if (isFirstRun)
	{
		isFirstRun = false;
		size_t i = 0;
		for (auto& data : cylindersData)
		{
			cylinders.push_back(std::make_unique<Cylinder>(data.baseRadius, data.topRadius, data.height, data.slices, data.stacks, data.style, data.isClose, data.lineWidth, data.r, data.g, data.b));
			cylinders[i]->Translate(data.transX, data.transY, data.transZ);
			cylinders[i]->Rotate(data.rotX, data.rotY, data.rotZ);
			cylinders[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			i++;
		}
		i = 0;
		for (auto& data : spheresData)
		{
			spheres.push_back(std::make_unique<Sphere>(data.radius, data.slices, data.stacks, data.style, data.lineWidth, data.r, data.g, data.b));
			spheres[i]->Translate(data.transX, data.transY, data.transZ);
			spheres[i]->Rotate(data.rotX, data.rotY, data.rotZ);
			spheres[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			i++;
		}
		i = 0;
		for (auto& data : cubesData)
		{
			cubes.push_back(std::make_unique<Cube>(data.length, data.width, data.height, data.r, data.g, data.b));
			cubes[i]->Translate(data.transX, data.transY, data.transZ);
			cubes[i]->Rotate(data.rotX, data.rotY, data.rotZ);
			cubes[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			i++;
		}
		i = 0;
		for (auto& data : pyramidsData)
		{
			pyramids.push_back(std::make_unique<Pyramid>(data.length, data.width, data.height, data.r, data.g, data.b));
			pyramids[i]->Translate(data.transX, data.transY, data.transZ);
			pyramids[i]->Rotate(data.rotX, data.rotY, data.rotZ);
			pyramids[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			i++;
		}
	}
	else
	{	
		// Press Enter can refresh data, able to modify the 3D shape in runtime 
		for (size_t i = 0; i < cylinders.size() && i < cylindersData.size(); i++) {
			cylinders[i]->SetBaseRadius(cylindersData[i].baseRadius);
			cylinders[i]->SetTopRadius(cylindersData[i].topRadius);
			cylinders[i]->SetHeight(cylindersData[i].height);
			cylinders[i]->SetSlices(cylindersData[i].slices);
			cylinders[i]->SetStacks(cylindersData[i].stacks);
			cylinders[i]->SetStyle(cylindersData[i].style);
			cylinders[i]->SetIsClose(cylindersData[i].isClose);
			cylinders[i]->SetLineWidth(cylindersData[i].lineWidth);
			cylinders[i]->SetColor(cylindersData[i].r, cylindersData[i].g, cylindersData[i].b);
			cylinders[i]->Translate(cylindersData[i].transX, cylindersData[i].transY, cylindersData[i].transZ);
			cylinders[i]->Rotate(cylindersData[i].rotX, cylindersData[i].rotY, cylindersData[i].rotZ);
			cylinders[i]->Scale(cylindersData[i].scaleX, cylindersData[i].scaleY, cylindersData[i].scaleZ);
		}

		for (size_t i = 0; i < spheres.size() && i < spheresData.size(); i++)
		{
			spheres[i]->SetRadius(spheresData[i].radius);
			spheres[i]->SetSlices(spheresData[i].slices);
			spheres[i]->SetStacks(spheresData[i].stacks);
			spheres[i]->SetStyle(spheresData[i].style);
			spheres[i]->SetLineWidth(spheresData[i].lineWidth);
			spheres[i]->SetColor(spheresData[i].r, spheresData[i].g, spheresData[i].b);
			spheres[i]->Translate(spheresData[i].transX, spheresData[i].transY, spheresData[i].transZ);
			spheres[i]->Rotate(spheresData[i].rotX, spheresData[i].rotY, spheresData[i].rotZ);
			spheres[i]->Scale(spheresData[i].scaleX, spheresData[i].scaleY, spheresData[i].scaleZ);
		}

		for (size_t i = 0; i < cubes.size() && i < cubesData.size(); i++)
		{
			cubes[i]->SetLength(cubesData[i].length);
			cubes[i]->SetWidth(cubesData[i].width);
			cubes[i]->SetHeight(cubesData[i].height);
			cubes[i]->SetColor(cubesData[i].r, cubesData[i].g, cubesData[i].b);
			cubes[i]->Translate(cubesData[i].transX, cubesData[i].transY, cubesData[i].transZ);
			cubes[i]->Rotate(cubesData[i].rotX, cubesData[i].rotY, cubesData[i].rotZ);
			cubes[i]->Scale(cubesData[i].scaleX, cubesData[i].scaleY, cubesData[i].scaleZ);
		}

		for (size_t i = 0; i < pyramids.size() && i < pyramidsData.size(); i++)
		{
			pyramids[i]->SetLength(pyramidsData[i].length);
			pyramids[i]->SetWidth(pyramidsData[i].width);
			pyramids[i]->SetHeight(pyramidsData[i].height);
			pyramids[i]->SetColor(pyramidsData[i].r, pyramidsData[i].g, pyramidsData[i].b);
			pyramids[i]->Translate(pyramidsData[i].transX, pyramidsData[i].transY, pyramidsData[i].transZ);
			pyramids[i]->Rotate(pyramidsData[i].rotX, pyramidsData[i].rotY, pyramidsData[i].rotZ);
			pyramids[i]->Scale(pyramidsData[i].scaleX, pyramidsData[i].scaleY, pyramidsData[i].scaleZ);
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

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	glEnable(GL_DEPTH_TEST);

	ReadData();
	
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}