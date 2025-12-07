#include "pch.h"
#include "Cube.h"

Cube::Cube(
	float length,
	float width,
	float height,
	float r,
	float g,
	float b
) :
	length(length),
	width(width),
	height(height),
	r(r),
	g(g),
	b(b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	centerX = length * 0.5f;
	centerY = height * 0.5f;
	centerZ = width * 0.5f;
}
Cube::~Cube()
{
}
;

void Cube::Draw() {

	glPushMatrix();

	// glColor3f(r, g, b);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);

	glTranslatef(transX, transY, transZ);

	if (isRotateByCenter)
	{
		glTranslatef(centerX, centerY, centerZ);
		if (isExpandable) glTranslatef(-centerX, -centerY, -centerZ);
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
		if (isExpandable) glTranslatef(centerX, centerY, centerZ);
	}
	else
	{
		glTranslatef(-rotPosX, -rotPosY, -rotPosZ);
	}

	glScalef(scaleX, scaleY, scaleZ);

	if (isExpandable) glTranslatef(-centerX, -centerY, -centerZ);

	glBegin(GL_QUADS);

	// back
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(length, 0.0f, 0.0f);
	glVertex3f(length, height, 0.0f);
	glVertex3f(0.0f, height, 0.0f);

	// front
	glVertex3f(0.0f, 0.0f, width);
	glVertex3f(length, 0.0f, width);
	glVertex3f(length, height, width);
	glVertex3f(0.0f, height, width);

	// left
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, width);
	glVertex3f(0.0f, height, width);
	glVertex3f(0.0f, height, 0.0f);

	// right
	glVertex3f(length, 0.0f, 0.0f);
	glVertex3f(length, 0.0f, width);
	glVertex3f(length, height, width);
	glVertex3f(length, height, 0.0f);

	// top
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(0.0f, height, width);
	glVertex3f(length, height, width);
	glVertex3f(length, height, 0.0f);

	// bottom
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, width);
	glVertex3f(length, 0.0f, width);
	glVertex3f(length, 0.0f, 0.0f);

	glEnd();

	glPopMatrix();
}

void Cube::Translate(float transX, float transY, float transZ) {
	this->transX = transX;
	this->transY = transY;
	this->transZ = transZ;
}

void Cube::Rotate(float rotX, float rotY, float rotZ, bool isRotateByCenter, float rotPosX, float rotPosY, float rotPosZ) {
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->isRotateByCenter = isRotateByCenter;
	this->rotPosX = rotPosX;
	this->rotPosY = rotPosY;
	this->rotPosZ = rotPosZ;
}

void Cube::Scale(float scaleX, float scaleY, float scaleZ){
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
}

// ======================
// Setters
// ======================
void Cube::SetLength(float l) {
	length = l;
	centerX = length * 0.5f;
}
void Cube::SetWidth(float w) {
	width = w;
	centerZ = width * 0.5f;
}
void Cube::SetHeight(float h) {
	height = h;
	centerY = height * 0.5f;
}
void Cube::SetColor(const std::array<float, 3>& c) {
	color[0] = c[0];
	color[1] = c[1];
	color[2] = c[2];
}
void Cube::SetColor(float red, float green, float blue) 
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Cube::SetExpandable(bool ex)
{
	isExpandable = ex;
}

// ======================
// Getters
// ======================

// size
float Cube::GetLength() const { return length; }
float Cube::GetWidth()  const { return width; }
float Cube::GetHeight() const { return height; }

// color
float Cube::GetR() const { return r; }
float Cube::GetG() const { return g; }
float Cube::GetB() const { return b; }
std::array<float, 3> Cube::GetColor() const {
	return { color[0], color[1], color[2] };
}
const float* Cube::GetColorPtr() const {
	return color;
}

// translate
float Cube::GetTransX() const { return transX; }
float Cube::GetTransY() const { return transY; }
float Cube::GetTransZ() const { return transZ; }

// rotate
float Cube::GetRotX() const { return rotX; }
float Cube::GetRotY() const { return rotY; }
float Cube::GetRotZ() const { return rotZ; }
bool  Cube::GetIsRotateByCenter() const { return isRotateByCenter; }

// scale
float Cube::GetScaleX() const { return scaleX; }
float Cube::GetScaleY() const { return scaleY; }
float Cube::GetScaleZ() const { return scaleZ; }

// center
float Cube::GetCenterX() const { return centerX; }
float Cube::GetCenterY() const { return centerY; }
float Cube::GetCenterZ() const { return centerZ; }

// rotate point
float Cube::GetRotPosX() const { return rotPosX; }
float Cube::GetRotPosY() const { return rotPosY; }
float Cube::GetRotPosZ() const { return rotPosZ; }

// expand in two way
bool Cube::GetIsExpandable() const { return isExpandable; }