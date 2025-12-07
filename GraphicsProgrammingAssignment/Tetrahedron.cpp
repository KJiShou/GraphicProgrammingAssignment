#include "pch.h"
#include "Tetrahedron.h"
#include "Math.h"

Tetrahedron::Tetrahedron(
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
};
Tetrahedron::~Tetrahedron() {

}

void Tetrahedron::Draw() {

	glPushMatrix();

	//glColor3f(r, g, b);
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

	Math::Vec3 A = { 0.0f, 0.0f, 0.0f };
	Math::Vec3 B = { length, 0.0f, 0.0f };
	Math::Vec3 C = { centerX, 0.0f, width };
	Math::Vec3 top = { centerX, height, centerZ };

	const Math::Vec3 shapeCenter = {
		(A.x + B.x + C.x + top.x) * 0.25f,
		(A.y + B.y + C.y + top.y) * 0.25f,
		(A.z + B.z + C.z + top.z) * 0.25f
	};

	auto emitFace = [&](const Math::Vec3& p1, const Math::Vec3& p2, const Math::Vec3& p3) {
		Math::Vec3 n = Math::CalcNormal(p1, p2, p3);
		Math::Vec3 faceCenter = {
			(p1.x + p2.x + p3.x) / 3.0f,
			(p1.y + p2.y + p3.y) / 3.0f,
			(p1.z + p2.z + p3.z) / 3.0f
		};
		Math::Vec3 toCenter = { shapeCenter.x - faceCenter.x, shapeCenter.y - faceCenter.y, shapeCenter.z - faceCenter.z };
		float dot = n.x * toCenter.x + n.y * toCenter.y + n.z * toCenter.z;
		if (dot > 0.0f) {
			n.x = -n.x; n.y = -n.y; n.z = -n.z;
		}
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
	};

	glBegin(GL_TRIANGLES);
	emitFace(A, B, C);     // base
	emitFace(A, B, top);   // back
	emitFace(B, C, top);   // right
	emitFace(C, A, top);   // left

	glEnd();

	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(length, 0.0f, 0.0f);
	//glVertex3f(length, 0.0f, width);
	//glVertex3f(0.0f, 0.0f, width);
	//glEnd();

	//glBegin(GL_TRIANGLE_FAN);
	//// center point
	//glVertex3f(centerX, height, centerZ);

	//// front	
	//glVertex3f(length, 0.0f, width);
	//glVertex3f(0.0f, 0.0f, width);

	//// back
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(length, 0.0f, 0.0f);

	//// right	
	//glVertex3f(length, 0.0f, 0.0f);
	//glVertex3f(length, 0.0f, width);

	//// left	
	//glVertex3f(0.0f, 0.0f, width);
	//glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();

	glPopMatrix();
}

void Tetrahedron::Translate(float transX, float transY, float transZ) {
	this->transX = transX;
	this->transY = transY;
	this->transZ = transZ;
}

void Tetrahedron::Rotate(float rotX, float rotY, float rotZ, bool isRotateByCenter, float rotPosX, float rotPosY, float rotPosZ) {
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->isRotateByCenter = isRotateByCenter;
	this->rotPosX = rotPosX;
	this->rotPosY = rotPosY;
	this->rotPosZ = rotPosZ;
}

void Tetrahedron::Scale(float scaleX, float scaleY, float scaleZ) {
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
}

// ======================
// Setters
// ======================
void Tetrahedron::SetLength(float l) {
	length = l;
	centerX = length * 0.5f;
}
void Tetrahedron::SetWidth(float w) {
	width = w;
	centerZ = width * 0.5f;
}
void Tetrahedron::SetHeight(float h) {
	height = h;
	centerY = height * 0.5f;
}

void Tetrahedron::SetColor(const std::array<float, 3>& c) {
	color[0] = c[0];
	color[1] = c[1];
	color[2] = c[2];
}
void Tetrahedron::SetColor(float red, float green, float blue)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}


// ======================
// Getters
// ======================

// size
float Tetrahedron::GetLength() const { return length; }
float Tetrahedron::GetWidth()  const { return width; }
float Tetrahedron::GetHeight() const { return height; }

// color
float Tetrahedron::GetR() const { return r; }
float Tetrahedron::GetG() const { return g; }
float Tetrahedron::GetB() const { return b; }
std::array<float, 3> Tetrahedron::GetColor() const {
	return { color[0], color[1], color[2] };
}
const float* Tetrahedron::GetColorPtr() const {
	return color;
}

// translate
float Tetrahedron::GetTransX() const { return transX; }
float Tetrahedron::GetTransY() const { return transY; }
float Tetrahedron::GetTransZ() const { return transZ; }

// rotate
float Tetrahedron::GetRotX() const { return rotX; }
float Tetrahedron::GetRotY() const { return rotY; }
float Tetrahedron::GetRotZ() const { return rotZ; }
bool  Tetrahedron::GetIsRotateByCenter() const { return isRotateByCenter; }

// scale
float Tetrahedron::GetScaleX() const { return scaleX; }
float Tetrahedron::GetScaleY() const { return scaleY; }
float Tetrahedron::GetScaleZ() const { return scaleZ; }

// center
float Tetrahedron::GetCenterX() const { return centerX; }
float Tetrahedron::GetCenterY() const { return centerY; }
float Tetrahedron::GetCenterZ() const { return centerZ; }

// rotate point
float Tetrahedron::GetRotPosX() const { return rotPosX; }
float Tetrahedron::GetRotPosY() const { return rotPosY; }
float Tetrahedron::GetRotPosZ() const { return rotPosZ; }
