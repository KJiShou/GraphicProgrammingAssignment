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
#define CLAMP(v, min, max) ((v < min) ? min : ((v > max) ? max : v))

using json = nlohmann::json;
json j;

//==================================
// Key Scheme
//==================================
// MODE 1 (Camera View) [Default]
// ---------------------------------
// Camera Movement
// W - Move To Front
// S - Move To Back
// A - Move To Left
// D - Move To Right
// Q - Move To Down
// E - Move To Up
// 
// Light Movement
// I - Move To Front
// K - Move To Back
// J - Move To Left
// L - Move To Right
// U - Move To Down
// O - Move To Up
// 
// Feature Key
// Z - Show/Close Axis Line
// X - Perspective view
// C - Ortho view
// V - Frustum view
// F1 - print Debug Info
//==================================
// MODE 2 (Robot Movement)
// ---------------------------------
// T - Move To Front
// G - Move To Back
// F - Move To Left
// H - Move To Right
// Space - Jump
// SHIFT - Sprint / Run
// Mouse Left Click - Attack(sword) and Shoot(Gun)
// Mouse Right Click - Block(shield) and Aim(Gun without shield)
// 1 - equip/drop sword
// 2 - equip/drop gun
// 3 - equip/drop shield
// 
// R - Reset Position
//==================================
// MODE 4 (Every Part Movement)
// ---------------------------------
// T - x(+)
// SHIFT + T - x(-)
// G - y(-)
// SHIFT + G - y(-)
// B - z(-)
// SHIFT + B - z(-)
// 
// Finger Rotation
// N -> thumb
// M -> Index
// , -> Middle
// . -> Ring
// / -> Little
// SHIFT - reverse order
// 
// R - Reset Position
// 
// 1 -> Head
// 2 -> Body
// 3 -> Left Upper Arm
// 4 -> Right Upper Arm
// 5 -> Left ForeArm
// 6 -> Right ForeArm
// 7 -> Left Hand
// 8 -> Right Hand
// 9 -> Left Up Leg
// 0 -> Right Up Leg
// - -> Left Low Leg
// = -> Right Low Leg
// [ -> Left Foot
// ] -> Right Foot
// \ -> wing
// ; -> left hand finger
// ' -> right hand finger
// F2 -> Pelvis
//==================================

// movement mode
int keyMode = 0;
int totalNumberKeyMode = 3;

int selectedPart = 1;

float head[3] = { 0 };
float body[3] = { 0, -16, 0 };
float pelvis[3] = { 0 };
float lUpArm[3] = { -45, 5, 0 }, rUpArm[3] = { 27, 68, 50 };
float lForeArm[2] = { 69, -4 }, rForeArm[2] = { 75, 89 };
float lHand[3] = { 26, -30, 8 }, rHand[3] = { -16, -18, 45 };
float lUpLeg[3] = { 90, 8, 60}, rUpLeg[3] = { 76, -11, -7 };
float lLowLeg[1] = { -94 }, rLowLeg[1] = { -85 };
float lFoot[3] = { -20, -2, -3 }, rFoot[3] = { -30, 2, 0 };
float lFinger[5] = { 0 }, rFinger[5] = { 90, 90, 90, 90, 90 };
float wing = 0.0f;
float jumpTimer = 0.0f;
float attackTimer = 0.0f;
float blockTimer = 0.0f;
float shootTimer = 0.0f;

struct Bullet {
	float x, y, z;
	float vx, vy, vz;
	bool active;
};

std::vector<Bullet> bullets;
bool hasSword = false;
bool hasGun = false;
bool hasShield = false;

float recoilTimer = 0.0f;
bool isFiring = false;

void ToggleSword();
void ToggleGun();
void ToggleShield();
void FireBullet();

// light
GLUquadricObj* var = gluNewQuadric();
Light light0 = Light( { 0.2f, 0.2f, 0.2f, 1.0f}, { 1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 10.0f, 5.0f, 1.0f}, GL_LIGHT0);
Cube c1 = Cube(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
Pyramid p1 = Pyramid(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
Tetrahedron t1 = Tetrahedron(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
Cylinder cylinder1 = Cylinder(1.0f, 1.0f, 0.0f, 1.0f, 50, 50, GLU_FILL, true, 1.0f, 1.0f, 1.0f, 1.0f);
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

TowerBridge* towerBridge = NULL;
Object* background = NULL;
BackBone* backbone = NULL;
Object* gun = NULL;
Object* sword = NULL;
Object* shield = NULL;

float camPosX = 0.0f, camPosY = 0.0f, camPosZ = 5.0f;
float camYaw = 0.0f;   // Y-axis rotation (left/right)
float camPitch = 0.0f; // X-axis rotation (up/down)

float x = 0, y = 0, z = 0;

HWND GetHWnd() { return hWnd; }

void ReadData() {
	//background->ReadData();
	backbone->ReadData();
	towerBridge->ReadData();
	gun->ReadData();
	sword->ReadData();
	shield->ReadData();
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

void ToggleSword() {
	if (hasSword) {
		backbone->leftHand->RemoveChild(sword);
		hasSword = false;
		backbone->RotateLeftHandFinger(0, 0, 0);
	}
	else {
		if (hasGun) ToggleGun();

		backbone->leftHand->AddChild(sword);
		hasSword = true;

		backbone->RotateLeftHandFinger(90, 90, 90);
	}
}

void ToggleGun() {
	if (hasGun) {
		backbone->leftHand->RemoveChild(gun);
		hasGun = false;
		backbone->RotateLeftHandFinger(0, 0, 0);
	}
	else {
		if (hasSword) ToggleSword();

		backbone->leftHand->AddChild(gun);
		hasGun = true;

		backbone->RotateLeftHandFinger(90, 90, 90);
		backbone->RotateLeftIndex(0.0f, 90.0f, 90.0f);
	}
}

void ToggleShield() {
	if (hasShield) {
		backbone->rightHand->RemoveChild(shield);
		hasShield = false;
		backbone->RotateRightHandFinger(0, 0, 0);
	}
	else {
		backbone->rightHand->AddChild(shield);
		hasShield = true;

		backbone->RotateRightHandFinger(90, 90, 90);
	}
}

void FireBullet() {
	float angleRad = (gameObjectRotY + 65) * PI / 180.0f;

	Bullet b;
	float offsetSide = 1.5f;

	float speed = 1.0f;

	b.vx = sin(angleRad) * speed;
	b.vz = cos(angleRad) * speed;
	b.vy = 0.0f;

	float offsetHeight = 3.2f;

	b.x = gameObjectTransX + 0.7;
	b.y = gameObjectTransY + offsetHeight;
	b.z = gameObjectTransZ + 1.0;

	b.active = true;
	bullets.push_back(b);
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
			if (keyMode == 0) {
				camPosX = 0.0f, camPosY = 0.0f, camPosZ = 5.0f;
				camYaw = 0.0f;
				camPitch = 0.0f;
			}
			break;
		}
		case VK_F1:
		{
			std::cout << std::fixed << std::setprecision(1);
			std::cout << "\n=== ROBOT POSE DEBUG INFO ===" << std::endl;
			// Head & Body
			std::cout << "Head:      x(" << head[0] << "), y(" << head[1] << "), z(" << head[2] << ")" << std::endl;
			std::cout << "Body:      x(" << body[0] << "), y(" << body[1] << "), z(" << body[2] << ")" << std::endl;
			std::cout << "Pelvis:      x(" << pelvis[0] << "), y(" << pelvis[1] << "), z(" << pelvis[2] << ")" << std::endl;
			std::cout << "-----------------------------" << std::endl;

			// Arms (Left)
			std::cout << "L.UpArm:   x(" << lUpArm[0] << "), y(" << lUpArm[1] << "), z(" << lUpArm[2] << ")" << std::endl;
			std::cout << "L.ForeArm: x(" << lForeArm[0] << "), y(" << lForeArm[1] << ")" << std::endl;
			std::cout << "L.Hand:    x(" << lHand[0] << "), y(" << lHand[1] << "), z(" << lHand[2] << ")" << std::endl;
			std::cout << "L.Finger:    1(" << lFinger[0] << "), 2(" << lFinger[1] << "), 3(" << lFinger[2] << "), 4(" << lFinger[3] << "), 5(" << lFinger[4] << ")" << std::endl;

			// Arms (Right)
			std::cout << "R.UpArm:   x(" << rUpArm[0] << "), y(" << rUpArm[1] << "), z(" << rUpArm[2] << ")" << std::endl;
			std::cout << "R.ForeArm: x(" << rForeArm[0] << "), y(" << rForeArm[1] << ")" << std::endl;
			std::cout << "R.Hand:    x(" << rHand[0] << "), y(" << rHand[1] << "), z(" << rHand[2] << ")" << std::endl;
			std::cout << "R.Finger:    1(" << rFinger[0] << "), 2(" << rFinger[1] << "), 3(" << rFinger[2] << "), 4(" << rFinger[3] << "), 5(" << rFinger[4] << ")" << std::endl;
			std::cout << "-----------------------------" << std::endl;

			// Legs (Left)
			std::cout << "L.UpLeg:   x(" << lUpLeg[0] << "), y(" << lUpLeg[1] << "), z(" << lUpLeg[2] << ")" << std::endl;
			std::cout << "L.LowLeg:  x(" << lLowLeg[0] << ")" << std::endl;
			std::cout << "L.Foot:    x(" << lFoot[0] << "), y(" << lFoot[1] << "), z(" << lFoot[2] << ")" << std::endl;

			// Legs (Right)
			std::cout << "R.UpLeg:   x(" << rUpLeg[0] << "), y(" << rUpLeg[1] << "), z(" << rUpLeg[2] << ")" << std::endl;
			std::cout << "R.LowLeg:  x(" << rLowLeg[0] << ")" << std::endl;
			std::cout << "R.Foot:    x(" << rFoot[0] << "), y(" << rFoot[1] << "), z(" << rFoot[2] << ")" << std::endl;
			std::cout << "-----------------------------" << std::endl;

			std::cout << "Wing:      (" << wing << ")" << std::endl;
			std::cout << "=============================" << std::endl;
			break;
		}
		case '1':
			if (keyMode == 1)
				ToggleSword();
			break;
		case '2':
			if (keyMode == 1)
				ToggleGun();
			break;
		case '3':
			if (keyMode == 1)
				ToggleShield();
			break;
		case 'R':
		{
			if (keyMode == 1) {
				gameObjectRotX = 0;
				gameObjectRotY = 0;
				gameObjectRotZ = 0;
				gameObjectTransX = 0;
				gameObjectTransY = 0;
				gameObjectTransZ = 0;
			}
			if (keyMode == 2) {
				head[0] = 0; head[1] = 0; head[2] = 0;
				body[0] = 0; body[1] = 0; body[2] = 0;
				pelvis[0] = 0; pelvis[1] = 0; pelvis[2] = 0;

				lUpArm[0] = 0; lUpArm[1] = 0; lUpArm[2] = 0;
				rUpArm[0] = 0; rUpArm[1] = 0; rUpArm[2] = 0;

				lForeArm[0] = 0; lForeArm[1] = 0;
				rForeArm[0] = 0; rForeArm[1] = 0;

				lHand[0] = 0; lHand[1] = 0; lHand[2] = 0;
				rHand[0] = 0; rHand[1] = 0; rHand[2] = 0;

				lUpLeg[0] = 0; lUpLeg[1] = 0; lUpLeg[2] = 0;
				rUpLeg[0] = 0; rUpLeg[1] = 0; rUpLeg[2] = 0;

				lLowLeg[0] = 0;
				rLowLeg[0] = 0;

				lFoot[0] = 0; lFoot[1] = 0; lFoot[2] = 0;
				rFoot[0] = 0; rFoot[1] = 0; rFoot[2] = 0;

				lFinger[0] = 0; lFinger[1] = 0; lFinger[2] = 0; lFinger[3] = 0; lFinger[4] = 0;
				rFinger[0] = 0; rFinger[1] = 0; rFinger[2] = 0; rFinger[3] = 0; rFinger[4] = 0;

				backbone->RotateHead(0, 0, 0);
				backbone->RotateBody(0, 0, 0);
				backbone->RotatePelvis(0, 0, 0);
				backbone->RotateLeftUpperArm(0, 0, 0);
				backbone->RotateRightUpperArm(0, 0, 0);
				backbone->RotateLeftForearm(0, 0);
				backbone->RotateRightForearm(0, 0);
				backbone->RotateLeftHand(0, 0, 0);
				backbone->RotateRightHand(0, 0, 0);
				backbone->RotateLeftUpperLeg(0, 0, 0);
				backbone->RotateRightUpperLeg(0, 0, 0);
				backbone->RotateLeftLowerLeg(0);
				backbone->RotateRightLowerLeg(0);
				backbone->RotateLeftFoot(0, 0, 0);
				backbone->RotateRightFoot(0, 0, 0);
				backbone->RotateLeftHandFinger(0, 0, 0);
				backbone->RotateRightHandFinger(0, 0, 0);
			}
			break;
		}
		case 'Z': {
			drawAxis = !drawAxis;
			break;
		}
		case 'C': {
			isOtho = true;
			isPerspective = false;
			isFrustrum = false;
			break;
		}
		case 'X': {
			isOtho = false;
			isPerspective = true;
			isFrustrum = false;
			break;
		}
		case 'V': {
			isOtho = false;
			isPerspective = false;
			isFrustrum = true;
			break;
		}
		case VK_TAB: {
			keyMode += 1;
			if (keyMode >= totalNumberKeyMode) keyMode = 0;
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
	//===============================
	// JS Testing Section
	//===============================
	/*backbone->RotateRightForearm(x, -90);
	backbone->RotateRightUpperArm(x, y, z);
	backbone->RotateLeftUpperArm(x, y, z);
	backbone->RotateLeftForearm(x, -90);
	backbone->RotateLeftHandFinger(x, y, z);
	backbone->RotateRightHandFinger(x, y, z);
	backbone->RotateRightUpperLeg(x, y, z);
	backbone->RotateRightLowerLeg(x);
	backbone->RotateRightFoot(x, y, z);
	backbone->RotateLeftUpperLeg(x, y, z);
	backbone->RotateBody(x, y, z);*/

	//===============================
	// JY Testing Section
	//===============================
	//backbone->RotateLeftUpperArm(90.0f, 0.0f, 0.0f);
	//backbone->RotateLeftHandFinger(90.0f, 90.0f, 90.0f);
	//backbone->RotateLeftThumb(0.0f, 0.0f, 0.0f);
	//backbone->RotateLeftIndex(0.0f, 90.0f, 90.0f);
	//backbone->RotateLeftMiddle(0.0f, 0.0f, 0.0f);
	//backbone->RotateLeftRing(0.0f, 0.0f, 0.0f);
	//backbone->RotateLeftLittle(0.0f, 0.0f, 0.0f);

	//backbone->RotateRightUpperArm(90.0f, 0.0f, 0.0f);
	//backbone->RotateRightHandFinger(90.0f, 90.0f, 90.0f);
	//backbone->RotateLeftThumb(0.0f, 0.0f, 0.0f);
	//backbone->RotateLeftIndex(0.0f, 90.0f, 90.0f);
	//backbone->RotateLeftMiddle(0.0f, 0.0f, 0.0f);
	//backbone->RotateLeftRing(0.0f, 0.0f, 0.0f);
	//backbone->RotateLeftLittle(0.0f, 0.0f, 0.0f);
	
	//===============================
	// HJ Testing Section
	//===============================
	//backbone->RotateLeftUpperArm(90.0f, 0.0f, 0.0f);
	//backbone->RotateLeftHandFinger(90.0f, 90.0f, 90.0f);
	//backbone->RotateLeftThumb(0.0f, 90.0f, 60.0f);
	//backbone->RotateLeftIndex(90.0f, 90.0f, 90.0f);
	//backbone->RotateLeftMiddle(0.0f, 0.0f, 0.0f);
	//backbone->RotateLeftRing(0.0f, 0.0f, 0.0f);
	//backbone->RotateLeftLittle(0.0f, 0.0f, 0.0f);
	


	// ==============================
	// Draw
	// ==============================
	backbone->Draw();

	glPushMatrix();
	glTranslatef(light0.GetPosition()[0], light0.GetPosition()[1], light0.GetPosition()[2]);
	GLfloat redColor[] = { 1.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, redColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redColor);
	gluSphere(var, 0.1f, 10.0f, 10.0f);
	glPopMatrix();

	c1.Translate(-10.0f, 0.0f, 10.0f);
	//c1.Draw();
	p1.Translate(-5.0f, 0.0f, 10.0f);
	//p1.Draw();
	t1.Translate(-15.0f, 0.0f, 10.0f);
	//t1.Draw();
	cylinder1.Translate(-20.0f, 0.0f, 10.0f);
	//cylinder1.Draw();
	sphere1.Translate(0.0f, 0.0f, 10.0f);
	//sphere1.Draw();
	frustumCube.Translate(5.0f, 0.0f, 10.0f);
	//frustumCube.Draw();

	glPushMatrix();
	glLoadIdentity();

	UpdateCameraView();
	glTranslatef(cameraTransX, cameraTransY, cameraTransZ);
	glRotatef(cameraRotateXAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraRotateYAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(cameraRotateZAngle, 0.0f, 0.0f, 1.0f);

	GLfloat yellowColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat noSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellowColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, noSpecular);

	for (const auto& b : bullets) {
		if (b.active) {
			glPushMatrix();
			glTranslatef(b.x, b.y, b.z);
			gluSphere(var, 0.1f, 8, 8);
			glPopMatrix();
		}
	}

	glPopMatrix();
	
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
	background->Draw();
	glEnable(GL_LIGHTING);
	UpdateCameraView();
	glTranslatef(cameraTransX, cameraTransY, cameraTransZ);
	glRotatef(cameraRotateXAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraRotateYAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(cameraRotateZAngle, 0.0f, 0.0f, 1.0f);

	light0.Update();

	
	

	
	Draw();
	
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------


float camNormalMoveSpeed = 0.05;
float camFasterMoveSpeed = 0.1;
void Update(int framesToUpdate) {
	CalcDeltaTime();
	for (int i = 0; i < framesToUpdate; i++) {
		globalFrameCounter++;

		camYaw -= input.GetMouseX() * 0.1f;
		camPitch -= input.GetMouseY() * 0.1f;

		if (camPitch > 89.0f)  camPitch = 89.0f;
		if (camPitch < -89.0f) camPitch = -89.0f;

		input.SetMouseX(0);
		input.SetMouseY(0);

		float speed = input.IsKeyPressed(DIK_LSHIFT) ? camFasterMoveSpeed : camNormalMoveSpeed;

		float forwardX = sinf(camYaw * PI / 180);
		float forwardZ = cosf(camYaw * PI / 180);

		float rightX = cosf(camYaw * PI / 180);
		float rightZ = -sinf(camYaw * PI / 180);

		if (input.IsKeyPressed(DIK_S))
			camPosX += forwardX * speed,
			camPosZ += forwardZ * speed;

		if (input.IsKeyPressed(DIK_W))
			camPosX -= forwardX * speed,
			camPosZ -= forwardZ * speed;

		if (input.IsKeyPressed(DIK_A))
			camPosX -= rightX * speed,
			camPosZ -= rightZ * speed;

		if (input.IsKeyPressed(DIK_D))
			camPosX += rightX * speed,
			camPosZ += rightZ * speed;

		if (input.IsKeyPressed(DIK_E)) {
			camPosY += speed;
		}
		if (input.IsKeyPressed(DIK_Q)) {
			camPosY -= speed;
		}

		if (keyMode == 1) {
			bool isAttacking = (backbone->GetState() == ATTACK);
			bool isJumping = (backbone->GetState() == JUMP);
			bool isBlocking = (backbone->GetState() == BLOCK);
			bool isShooting = (backbone->GetState() == SHOOT);

			bool isMoving = false;
			bool isRunning = input.IsKeyPressed(DIK_LSHIFT);
			float moveSpeed = isRunning ? 0.15f : 0.05f;
			AnimState targetMoveAnim = isRunning ? RUN : WALK;

			if (isJumping) {
				jumpTimer += 0.016f;
				if (jumpTimer > 1.64f) {
					backbone->SetState(IDLE);
					isJumping = false;
					jumpTimer = 0.0f;
				}
			}

			if (isAttacking) {
				attackTimer += 0.016f;
				if (attackTimer > 1.26f) {
					backbone->SetState(IDLE);
					isAttacking = false;
					attackTimer = 0.0f;
				}
			}

			if (isBlocking) {
				blockTimer += 0.016f;
				if (gameObjectTransY > -0.4) gameObjectTransY -= 0.016;
				if (blockTimer > 1.0f) {
					backbone->SetState(IDLE);
					gameObjectTransY = 0;
					isBlocking = false;
					blockTimer = 0.0f;
				}
			}

			if (input.IsKeyPressed(DIK_F)) {
				if (!isJumping && !isAttacking && !isBlocking && !isShooting && backbone->GetState() != targetMoveAnim) {
					backbone->SetState(targetMoveAnim);
				}
				if (!isShooting && !isBlocking) gameObjectTransX -= moveSpeed;
				if (!isShooting && !isBlocking) gameObjectRotY = -90;
				isMoving = true;
			}
			else if (input.IsKeyPressed(DIK_H)) {
				if (!isJumping && !isAttacking && !isBlocking && !isShooting && backbone->GetState() != targetMoveAnim) {
					backbone->SetState(targetMoveAnim);
				}
				if (!isShooting && !isBlocking) gameObjectTransX += moveSpeed;
				if (!isShooting && !isBlocking) gameObjectRotY = 90;
				isMoving = true;
			}
			else if (input.IsKeyPressed(DIK_G)) {
				if (!isJumping && !isAttacking && !isBlocking && !isShooting && backbone->GetState() != targetMoveAnim) {
					backbone->SetState(targetMoveAnim);
				}
				if (!isShooting && !isBlocking) gameObjectTransZ += moveSpeed;
				if (!isShooting && !isBlocking) gameObjectRotY = 0;
				isMoving = true;
			}
			else if (input.IsKeyPressed(DIK_T)) {
				if (!isJumping && !isAttacking && !isBlocking && !isShooting && backbone->GetState() != targetMoveAnim) {
					backbone->SetState(targetMoveAnim);
				}
				if (!isShooting && !isBlocking) gameObjectTransZ -= moveSpeed;
				if (!isShooting && !isBlocking) gameObjectRotY = 180;
				isMoving = true;
			}

			if (input.IsLeftMouseDown()) {
				if (hasSword && !isJumping && !isBlocking && !isShooting) {
					if (backbone->GetState() != ATTACK) {
						backbone->SetState(ATTACK);
						attackTimer = 0.0f;
					}
					isMoving = true;
				}
				else if (hasGun && isShooting) {
					if (!isFiring) {
						FireBullet();
						isFiring = true;
						recoilTimer = 0.0f;
					}
				}
			}
			else {
				if (isFiring) isFiring = false;
			}

			if (input.IsRightMouseDown()) {
				if (hasShield && !isAttacking && !isJumping && !isShooting) {
					if (backbone->GetState() != BLOCK) {
						backbone->SetState(BLOCK);
						blockTimer = 0.0f;
					}
					isMoving = true;
				}
				else if (hasGun && !isAttacking && !isJumping && !isBlocking) {
					if (!isShooting) {
						backbone->SetState(SHOOT);
					}
					isShooting = true;
				}
			}
			else {
				if (isShooting) {
					backbone->SetState(IDLE);
					isShooting = false;
				}
			}

			if (isFiring && recoilTimer < 0.2f) {
				recoilTimer += 0.016f;
				float recoil = (rand() % 10 - 5) * 0.5f;
				gameObjectRotX = recoil;
			}
			else if (recoilTimer >= 0.2f && recoilTimer < 0.3f) {
				gameObjectRotX = 0;
				recoilTimer = 1.0f;
			}

			for (auto& b : bullets) {
				if (b.active) {
					b.x += b.vx;
					b.y += b.vy;
					b.z += b.vz;

					if (abs(b.x) > 50 || abs(b.z) > 50) b.active = false;
				}
			}
			
			bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
				[](const Bullet& b) { return !b.active; }), bullets.end());

			if (!isMoving && !isJumping && !isAttacking && !isBlocking && !isShooting) {
				if (backbone->GetState() != IDLE) backbone->SetState(IDLE);
			}

			if (input.IsKeyPressed(DIK_SPACE)) {
				if (!isJumping && !isAttacking && !isBlocking && !isShooting) {
					backbone->SetState(JUMP);
					jumpTimer = 0.0f;
				}
			}

			backbone->Rotate(gameObjectRotX, gameObjectRotY + sin(deltaTime * 5.0f) * 2.0f, gameObjectRotZ);
			backbone->Move(gameObjectTransX, gameObjectTransY, gameObjectTransZ);
		}

		if (input.IsKeyPressed(DIK_J)) light0.Move(light0.GetPosition()[0] - 0.1f, light0.GetPosition()[1], light0.GetPosition()[2]);
		if (input.IsKeyPressed(DIK_L)) light0.Move(light0.GetPosition()[0] + 0.1f, light0.GetPosition()[1], light0.GetPosition()[2]);
		if (input.IsKeyPressed(DIK_U)) light0.Move(light0.GetPosition()[0], light0.GetPosition()[1] - 0.1f, light0.GetPosition()[2]);
		if (input.IsKeyPressed(DIK_O)) light0.Move(light0.GetPosition()[0], light0.GetPosition()[1] + 0.1f, light0.GetPosition()[2]);
		if (input.IsKeyPressed(DIK_I)) light0.Move(light0.GetPosition()[0], light0.GetPosition()[1], light0.GetPosition()[2] - 0.1f);
		if (input.IsKeyPressed(DIK_K)) light0.Move(light0.GetPosition()[0], light0.GetPosition()[1], light0.GetPosition()[2] + 0.1f);
	}

	if (keyMode == 2) {
		if (input.IsKeyPressed(DIK_1)) selectedPart = 1; // Head
		if (input.IsKeyPressed(DIK_2)) selectedPart = 2; // Body
		if (input.IsKeyPressed(DIK_3)) selectedPart = 3; // L.UpArm
		if (input.IsKeyPressed(DIK_4)) selectedPart = 4; // R.UpArm
		if (input.IsKeyPressed(DIK_5)) selectedPart = 5; // L.ForeArm
		if (input.IsKeyPressed(DIK_6)) selectedPart = 6; // R.ForeArm
		if (input.IsKeyPressed(DIK_7)) selectedPart = 7; // L.Hand
		if (input.IsKeyPressed(DIK_8)) selectedPart = 8; // R.Hand
		if (input.IsKeyPressed(DIK_9)) selectedPart = 9; // L.UpLeg
		if (input.IsKeyPressed(DIK_0)) selectedPart = 10; // R.UpLeg
		if (input.IsKeyPressed(DIK_MINUS)) selectedPart = 11; // L.LowLeg
		if (input.IsKeyPressed(DIK_EQUALS)) selectedPart = 12; // R.LowLeg
		if (input.IsKeyPressed(DIK_LBRACKET)) selectedPart = 13; // L.Foot
		if (input.IsKeyPressed(DIK_RBRACKET)) selectedPart = 14; // R.Foot
		if (input.IsKeyPressed(DIK_BACKSLASH)) selectedPart = 15; // Wing
		if (input.IsKeyPressed(DIK_SEMICOLON)) selectedPart = 16; // left hand finger
		if (input.IsKeyPressed(DIK_APOSTROPHE)) selectedPart = 17; // left hand finger
		if (input.IsKeyPressed(DIK_F2)) selectedPart = 18; // pelvis

		float spd = 1.0f;
		float dX = 0, dY = 0, dZ = 0;
		float f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0;

		if (input.IsKeyPressed(DIK_T)) {
			if (input.IsKeyPressed(DIK_LSHIFT) || input.IsKeyPressed(DIK_RSHIFT)) {
				dX -= spd;
			}
			else {
				dX += spd;
			}
		}
		if (input.IsKeyPressed(DIK_G)) {
			if (input.IsKeyPressed(DIK_LSHIFT) || input.IsKeyPressed(DIK_RSHIFT)) {
				dY -= spd;
			}
			else {
				dY += spd;
			}
		}

		if (input.IsKeyPressed(DIK_B)) {
			if (input.IsKeyPressed(DIK_LSHIFT) || input.IsKeyPressed(DIK_RSHIFT)) {
				dZ -= spd;
			}
			else {
				dZ += spd;
			}
		}

		if (input.IsKeyPressed(DIK_N)) {
			if (input.IsKeyPressed(DIK_LSHIFT)) {
				f1 -= spd;
			}
			else {
				f1 += spd;
			}
		}
		if (input.IsKeyPressed(DIK_M)) {
			if (input.IsKeyPressed(DIK_LSHIFT)) {
				f2 -= spd;
			}
			else {
				f2 += spd;
			}
		}
		if (input.IsKeyPressed(DIK_COMMA)) {
			if (input.IsKeyPressed(DIK_LSHIFT)) {
				f3 -= spd;
			}
			else {
				f3 += spd;
			}
		}
		if (input.IsKeyPressed(DIK_PERIOD)) {
			if (input.IsKeyPressed(DIK_LSHIFT)) {
				f4 -= spd;
			}
			else {
				f4 += spd;
			}
		}
		if (input.IsKeyPressed(DIK_SLASH)) {
			if (input.IsKeyPressed(DIK_LSHIFT)) {
				f5 -= spd;
			}
			else {
				f5 += spd;
			}
		}


		switch (selectedPart) {
		case 1:
			head[0] = CLAMP(head[0] + dX, -40.0f, 40.0f);
			head[1] = CLAMP(head[1] + dY, -70.0f, 70.0f);
			head[2] = CLAMP(head[2] + dZ, -30.0f, 30.0f);
			backbone->RotateHead(head[0], head[1], head[2]);
			break;

		case 2:
			body[0] = CLAMP(body[0] + dX, -30.0f, 30.0f);
			body[1] = CLAMP(body[1] + dY, -45.0f, 45.0f);
			body[2] = CLAMP(body[2] + dZ, -20.0f, 20.0f);
			backbone->RotateBody(body[0], body[1], body[2]);
			break;

		case 3:
			lUpArm[0] = CLAMP(lUpArm[0] + dX, -45.0f, 180.0f);
			lUpArm[1] = CLAMP(lUpArm[1] + dY, -90.0f, 90.0f);
			lUpArm[2] = CLAMP(lUpArm[2] + dZ, -20.0f, 100.0f);
			backbone->RotateLeftUpperArm(lUpArm[0], lUpArm[1], lUpArm[2]);
			break;

		case 4:
			rUpArm[0] = CLAMP(rUpArm[0] + dX, -45.0f, 180.0f);
			rUpArm[1] = CLAMP(rUpArm[1] + dY, -90.0f, 90.0f);
			rUpArm[2] = CLAMP(rUpArm[2] + dZ, -20.0f, 100.0f);
			backbone->RotateRightUpperArm(rUpArm[0], rUpArm[1], rUpArm[2]);
			break;

		case 5:
			lForeArm[0] = CLAMP(lForeArm[0] + dX, 0.0f, 140.0f);
			lForeArm[1] = CLAMP(lForeArm[1] + dY, -90.0f, 90.0f);
			backbone->RotateLeftForearm(lForeArm[0], lForeArm[1]);
			break;

		case 6:
			rForeArm[0] = CLAMP(rForeArm[0] + dX, 0.0f, 140.0f);
			rForeArm[1] = CLAMP(rForeArm[1] + dY, -90.0f, 90.0f);
			backbone->RotateRightForearm(rForeArm[0], rForeArm[1]);
			break;

		case 7:
			lHand[0] = CLAMP(lHand[0] + dX, -45.0f, 45.0f);
			lHand[1] = CLAMP(lHand[1] + dY, -30.0f, 30.0f);
			lHand[2] = CLAMP(lHand[2] + dZ, -45.0f, 45.0f);
			backbone->RotateLeftHand(lHand[0], lHand[1], lHand[2]);
			break;

		case 8:
			rHand[0] = CLAMP(rHand[0] + dX, -45.0f, 45.0f);
			rHand[1] = CLAMP(rHand[1] + dY, -30.0f, 30.0f);
			rHand[2] = CLAMP(rHand[2] + dZ, -45.0f, 45.0f);
			backbone->RotateRightHand(rHand[0], rHand[1], rHand[2]);
			break;

		case 9:
			lUpLeg[0] = CLAMP(lUpLeg[0] + dX, -120.0f, 90.0f);
			lUpLeg[1] = CLAMP(lUpLeg[1] + dY, -45.0f, 45.0f);
			lUpLeg[2] = CLAMP(lUpLeg[2] + dZ, -15.0f, 60.0f);
			backbone->RotateLeftUpperLeg(lUpLeg[0], lUpLeg[1], lUpLeg[2]);
			break;

		case 10:
			rUpLeg[0] = CLAMP(rUpLeg[0] + dX, -120.0f, 90.0f);
			rUpLeg[1] = CLAMP(rUpLeg[1] + dY, -45.0f, 45.0f);
			rUpLeg[2] = CLAMP(rUpLeg[2] + dZ, -15.0f, 60.0f);
			backbone->RotateRightUpperLeg(rUpLeg[0], rUpLeg[1], rUpLeg[2]);
			break;

		case 11:
			lLowLeg[0] = CLAMP(lLowLeg[0] + dX, -130.0f, 0.0f);
			backbone->RotateLeftLowerLeg(lLowLeg[0]);
			break;

		case 12:
			rLowLeg[0] = CLAMP(rLowLeg[0] + dX, -130.0f, 0.0f);
			backbone->RotateRightLowerLeg(rLowLeg[0]);
			break;

		case 13:
			lFoot[0] = CLAMP(lFoot[0] + dX, -30.0f, 45.0f);
			lFoot[1] = CLAMP(lFoot[1] + dY, -30.0f, 30.0f);
			lFoot[2] = CLAMP(lFoot[2] + dZ, -15.0f, 15.0f);
			backbone->RotateLeftFoot(lFoot[0], lFoot[1], lFoot[2]);
			break;

		case 14:
			rFoot[0] = CLAMP(rFoot[0] + dX, -30.0f, 45.0f);
			rFoot[1] = CLAMP(rFoot[1] + dY, -30.0f, 30.0f);
			rFoot[2] = CLAMP(rFoot[2] + dZ, -15.0f, 15.0f);
			backbone->RotateRightFoot(rFoot[0], rFoot[1], rFoot[2]);
			break;
		case 15:
			wing = CLAMP(wing + dY, -40.0f, 45.0f);
			backbone->RotateWing(wing, wing);
			break;
		case 16:
			lFinger[0] = CLAMP(lFinger[0] + f1, 0.0f, 90.0f);
			lFinger[1] = CLAMP(lFinger[1] + f2, 0.0f, 90.0f);
			lFinger[2] = CLAMP(lFinger[2] + f3, 0.0f, 90.0f);
			lFinger[3] = CLAMP(lFinger[3] + f4, 0.0f, 90.0f);
			lFinger[4] = CLAMP(lFinger[4] + f5, 0.0f, 90.0f);
			backbone->RotateLeftThumb(lFinger[0], lFinger[0], lFinger[0]);
			backbone->RotateLeftIndex(lFinger[1], lFinger[1], lFinger[1]);
			backbone->RotateLeftMiddle(lFinger[2], lFinger[2], lFinger[2]);
			backbone->RotateLeftRing(lFinger[3], lFinger[3], lFinger[3]);
			backbone->RotateLeftLittle(lFinger[4], lFinger[4], lFinger[4]);
			break;
		case 17:
			rFinger[0] = CLAMP(rFinger[0] + f1, 0.0f, 90.0f);
			rFinger[1] = CLAMP(rFinger[1] + f2, 0.0f, 90.0f);
			rFinger[2] = CLAMP(rFinger[2] + f3, 0.0f, 90.0f);
			rFinger[3] = CLAMP(rFinger[3] + f4, 0.0f, 90.0f);
			rFinger[4] = CLAMP(rFinger[4] + f5, 0.0f, 90.0f);
			backbone->RotateRightThumb(rFinger[0], rFinger[0], rFinger[0]);
			backbone->RotateRightIndex(rFinger[1], rFinger[1], rFinger[1]);
			backbone->RotateRightMiddle(rFinger[2], rFinger[2], rFinger[2]);
			backbone->RotateRightRing(rFinger[3], rFinger[3], rFinger[3]);
			backbone->RotateRightLittle(rFinger[4], rFinger[4], rFinger[4]);
			break;
		case 18:
			pelvis[0] = CLAMP(pelvis[0] + dX, -30.0f, 30.0f);
			pelvis[1] = CLAMP(pelvis[1] + dY, -45.0f, 45.0f);
			pelvis[2] = CLAMP(pelvis[2] + dZ, -20.0f, 20.0f);
			backbone->RotatePelvis(pelvis[0], pelvis[1], pelvis[2]);
			break;
		}
	}
	if (keyMode != 2) backbone->Animate(deltaTime);
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
	
	//LoadTexture("Assets/meme1.bmp", tex1, true);
	/*c1.SetAllTextures(tex1);
	p1.SetAllTextures(tex1);
	t1.SetAllTextures(tex1);
	cylinder1.SetAllTextures(tex1);
	sphere1.SetSphereTexture(tex1);
	frustumCube.SetAllTextures(tex1);*/

	ZeroMemory(&msg, sizeof(msg));
	backbone = new BackBone();
	backbone->SetBone();

	ShowCursor(true);

	towerBridge = new TowerBridge();
	background = new Object("background.json");
	gun = new Object("gun.json");
	sword = new Object("sword.json");
	shield = new Object("shield.json");
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
