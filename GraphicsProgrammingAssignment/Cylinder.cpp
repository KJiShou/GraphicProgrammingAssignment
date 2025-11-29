#include "pch.h"
#include "Cylinder.h"

Cylinder::Cylinder(
	float baseRadius,
	float topRadius,
	float height,
	int slices,
	int stacks,
	GLenum style,
	bool isClose,
	float lineWidth,
	float r,
	float g,
	float b
) :
	baseRadius(baseRadius),
	topRadius(topRadius),
	height(height),
	slices(slices),
	stacks(stacks),
	style(style),
	isClose(isClose),
	lineWidth(lineWidth),
	r(r),
	g(g),
	b(b)
{
	obj = gluNewQuadric();
	SetCenterPoint();
};

Cylinder::~Cylinder() {
	if (obj)
	{
		gluDeleteQuadric(obj);
	}
}

void Cylinder::Draw() {

	glPushMatrix();

	gluQuadricDrawStyle(obj, style);

	glColor3f(r, g, b);

	glTranslatef(transX, transY, transZ);

	if (isRotateByCenter)
	{
		glTranslatef(centerX, centerY, centerZ);
	}
	else
	{
		glTranslatef(rotPosX, rotPosY, rotPosZ);
	}

	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

	if (isRotateByCenter)
	{
		glTranslatef(-centerX, -centerY, -centerZ);
	}
	else
	{
		glTranslatef(-rotPosX, -rotPosY, -rotPosZ);
	}

	glScalef(scaleX, scaleY, scaleZ);

	gluCylinder(obj, baseRadius, topRadius, height, slices, stacks);

	if (isClose)
	{
		glPushMatrix();
		// bottom
		gluDisk(obj, 0.0f, baseRadius, slices, stacks);

		// top
		glTranslatef(0.0f, 0.0f, height);
		gluDisk(obj, 0.0f, topRadius, slices, stacks);
		glPopMatrix();
	}

	glPopMatrix();
}

void Cylinder::Translate(float transX, float transY, float transZ) {
	this->transX = transX;
	this->transY = transY;
	this->transZ = transZ;
}

void Cylinder::Rotate(float rotX, float rotY, float rotZ, bool isRotateByCenter, float rotPosX, float rotPosY, float rotPosZ) {
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->isRotateByCenter = isRotateByCenter;
	this->rotPosX = rotPosX;
	this->rotPosY = rotPosY;
	this->rotPosZ = rotPosZ;
}

void Cylinder::Scale(float scaleX, float scaleY, float scaleZ) {
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
}

void Cylinder::SetCenterPoint() {
	centerX = 0.0f;
	centerY = 0.0f;
	centerZ = height * 0.5f;
}

// ======================
// Setters
// ======================
void Cylinder::SetBaseRadius(float r) { baseRadius = r; }
void Cylinder::SetTopRadius(float r) { topRadius = r; }
void Cylinder::SetHeight(float h) { height = h; }
void Cylinder::SetLineWidth(float l) { lineWidth = l; }
void Cylinder::SetSlices(int s) { slices = s; }
void Cylinder::SetStacks(int s) { stacks = s; }
void Cylinder::SetStyle(GLenum s) { style = s; }
void Cylinder::SetIsClose(bool c) { style = c; }

void Cylinder::SetColor(float red, float green, float blue)
{
	r = red;
	g = green;
	b = blue;
}

// ======================
// Getters
// ======================
//GLUquadricObj* Cylinder::GetObj() const { return obj; };
GLenum Cylinder::GetStyle() const { return style; };
bool Cylinder::GetIsClose() const { return isClose; };

// size
float Cylinder::GetBaseRadius() const { return baseRadius; }
float Cylinder::GetTopRadius()  const { return topRadius; }
float Cylinder::GetHeight() const { return height; }
float Cylinder::GetLineWidth() const { return lineWidth; }
int Cylinder::GetSlices() const { return slices; }
int Cylinder::GetStacks() const { return stacks; }

// color
float Cylinder::GetR() const { return r; }
float Cylinder::GetG() const { return g; }
float Cylinder::GetB() const { return b; }

// translate
float Cylinder::GetTransX() const { return transX; }
float Cylinder::GetTransY() const { return transY; }
float Cylinder::GetTransZ() const { return transZ; }

// rotate
float Cylinder::GetRotX() const { return rotX; }
float Cylinder::GetRotY() const { return rotY; }
float Cylinder::GetRotZ() const { return rotZ; }
bool  Cylinder::GetIsRotateByCenter() const { return isRotateByCenter; }

// scale
float Cylinder::GetScaleX() const { return scaleX; }
float Cylinder::GetScaleY() const { return scaleY; }
float Cylinder::GetScaleZ() const { return scaleZ; }

// center
float Cylinder::GetCenterX() const { return centerX; }
float Cylinder::GetCenterY() const { return centerY; }
float Cylinder::GetCenterZ() const { return centerZ; }

// rotate point
float Cylinder::GetRotPosX() const { return rotPosX; }
float Cylinder::GetRotPosY() const { return rotPosY; }
float Cylinder::GetRotPosZ() const { return rotPosZ; }