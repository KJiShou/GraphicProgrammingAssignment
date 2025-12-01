#include "pch.h"
#include "Pyramid.h"

Pyramid::Pyramid(
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
	centerX = length * 0.5f;
	centerY = height * 0.5f;
	centerZ = width * 0.5f;
};
Pyramid::~Pyramid() {

}

void Pyramid::Draw() {

	glPushMatrix();

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

	// base
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(length, 0.0f, 0.0f);
	glVertex3f(length, 0.0f, width);
	glVertex3f(0.0f, 0.0f, width);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	// center point
	glVertex3f(centerX, height, centerZ);

	// front	
	glVertex3f(length, 0.0f, width);
	glVertex3f(0.0f, 0.0f, width);

	// back
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(length, 0.0f, 0.0f);

	// right	
	glVertex3f(length, 0.0f, 0.0f);
	glVertex3f(length, 0.0f, width);

	// left	
	glVertex3f(0.0f, 0.0f, width);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();

	glPopMatrix();
}

void Pyramid::Translate(float transX, float transY, float transZ) {
	this->transX = transX;
	this->transY = transY;
	this->transZ = transZ;
}

void Pyramid::Rotate(float rotX, float rotY, float rotZ, bool isRotateByCenter, float rotPosX, float rotPosY, float rotPosZ) {
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->isRotateByCenter = isRotateByCenter;
	this->rotPosX = rotPosX;
	this->rotPosY = rotPosY;
	this->rotPosZ = rotPosZ;
}

void Pyramid::Scale(float scaleX, float scaleY, float scaleZ) {
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
}

// ======================
// Setters
// ======================
void Pyramid::SetLength(float l) { 
	length = l; 
	centerX = length * 0.5f;
}
void Pyramid::SetWidth(float w) { 
	width = w; 
	centerZ = width * 0.5f;
}
void Pyramid::SetHeight(float h) { 
	height = h; 
	centerY = height * 0.5f;
}

void Pyramid::SetColor(float red, float green, float blue)
{
	r = red;
	g = green;
	b = blue;
}

// ======================
// Getters
// ======================

// size
float Pyramid::GetLength() const { return length; }
float Pyramid::GetWidth()  const { return width; }
float Pyramid::GetHeight() const { return height; }

// color
float Pyramid::GetR() const { return r; }
float Pyramid::GetG() const { return g; }
float Pyramid::GetB() const { return b; }

// translate
float Pyramid::GetTransX() const { return transX; }
float Pyramid::GetTransY() const { return transY; }
float Pyramid::GetTransZ() const { return transZ; }

// rotate
float Pyramid::GetRotX() const { return rotX; }
float Pyramid::GetRotY() const { return rotY; }
float Pyramid::GetRotZ() const { return rotZ; }
bool  Pyramid::GetIsRotateByCenter() const { return isRotateByCenter; }

// scale
float Pyramid::GetScaleX() const { return scaleX; }
float Pyramid::GetScaleY() const { return scaleY; }
float Pyramid::GetScaleZ() const { return scaleZ; }

// center
float Pyramid::GetCenterX() const { return centerX; }
float Pyramid::GetCenterY() const { return centerY; }
float Pyramid::GetCenterZ() const { return centerZ; }

// rotate point
float Pyramid::GetRotPosX() const { return rotPosX; }
float Pyramid::GetRotPosY() const { return rotPosY; }
float Pyramid::GetRotPosZ() const { return rotPosZ; }