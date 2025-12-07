#include "pch.h"
#include "Sphere.h"

Sphere::Sphere(
	float radius,
	int slices,
	int stacks,
	GLenum style,
	float lineWidth,
	float r,
	float g,
	float b
) :
	radius(radius),
	slices(slices),
	stacks(stacks),
	style(style),
	lineWidth(lineWidth),
	r(r),
	g(g),
	b(b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	obj = gluNewQuadric();
	centerX = 0.0f;
	centerY = 0.0f;
	centerZ = 0.0f;
};

Sphere::~Sphere() {
	if (obj)
	{
		gluDeleteQuadric(obj);
	}
}

void Sphere::Draw() {

	glPushMatrix();

	gluQuadricDrawStyle(obj, style);

	// glColor3f(r, g, b);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);

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
	
	gluSphere(obj, radius, slices, stacks);

	glPopMatrix();
}

void Sphere::Translate(float transX, float transY, float transZ) {
	this->transX = transX;
	this->transY = transY;
	this->transZ = transZ;
}

void Sphere::Rotate(float rotX, float rotY, float rotZ, bool isRotateByCenter, float rotPosX, float rotPosY, float rotPosZ) {
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->isRotateByCenter = isRotateByCenter;
	this->rotPosX = rotPosX;
	this->rotPosY = rotPosY;
	this->rotPosZ = rotPosZ;
}

void Sphere::Scale(float scaleX, float scaleY, float scaleZ) {
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
}

// ======================
// Setters
// ======================
void Sphere::SetRadius(float r) { radius = r; }
void Sphere::SetLineWidth(float l) { lineWidth = l; }
void Sphere::SetSlices(int s) { slices = s; }
void Sphere::SetStacks(int s) { stacks = s; }
void Sphere::SetStyle(GLenum s) { style = s; }

void Sphere::SetColor(const std::array<float, 3>& c) {
	color[0] = c[0];
	color[1] = c[1];
	color[2] = c[2];
}
void Sphere::SetColor(float red, float green, float blue)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

// ======================
// Getters
// ======================
//GLUquadricObj* Sphere::GetObj() const { return obj; };
GLenum Sphere::GetStyle() const { return style; };

// size
float Sphere::GetRadius() const { return radius; }
float Sphere::GetLineWidth() const { return lineWidth; }
int Sphere::GetSlices() const { return slices; }
int Sphere::GetStacks() const { return stacks; }

// color
float Sphere::GetR() const { return r; }
float Sphere::GetG() const { return g; }
float Sphere::GetB() const { return b; }
std::array<float, 3> Sphere::GetColor() const {
	return { color[0], color[1], color[2] };
}
const float* Sphere::GetColorPtr() const {
	return color;
}

// translate
float Sphere::GetTransX() const { return transX; }
float Sphere::GetTransY() const { return transY; }
float Sphere::GetTransZ() const { return transZ; }

// rotate
float Sphere::GetRotX() const { return rotX; }
float Sphere::GetRotY() const { return rotY; }
float Sphere::GetRotZ() const { return rotZ; }
bool  Sphere::GetIsRotateByCenter() const { return isRotateByCenter; }

// scale
float Sphere::GetScaleX() const { return scaleX; }
float Sphere::GetScaleY() const { return scaleY; }
float Sphere::GetScaleZ() const { return scaleZ; }

// center
float Sphere::GetCenterX() const { return centerX; }
float Sphere::GetCenterY() const { return centerY; }
float Sphere::GetCenterZ() const { return centerZ; }

// rotate point
float Sphere::GetRotPosX() const { return rotPosX; }
float Sphere::GetRotPosY() const { return rotPosY; }
float Sphere::GetRotPosZ() const { return rotPosZ; }