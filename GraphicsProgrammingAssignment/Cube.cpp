#include "pch.h"
#include "Cube.h"
#include "Math.h"

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

	Math::Vec3 A, B, C, D, normal;
	A = { 0.0f, 0.0f, width };
	B = { length, 0.0f, width };
	C = { length, height, width };
	D = { 0.0f, height, width };
	normal = Math::CalcNormal(A, B, C);
	std::cout << "front x: " << normal.x << std::endl;
	std::cout << "front y: " << normal.y << std::endl;
	std::cout << "front z: " << normal.z << std::endl;

	A = { 0.0f, 0.0f, 0.0f };
	B = { length, 0.0f, 0.0f };
	C = { length, height, 0.0f };
	D = { 0.0f, height, 0.0f };
	normal = Math::CalcNormal(A, B, C);
	std::cout << "back x: " << normal.x << std::endl;
	std::cout << "back y: " << normal.y << std::endl;
	std::cout << "back z: " << normal.z << std::endl;

	A = { 0.0f, 0.0f, 0.0f };
	B = { 0.0f, 0.0f, width };
	C = { 0.0f, height, width };
	D = { 0.0f, height, 0.0f };
	normal = Math::CalcNormal(A, B, C);
	std::cout << "left x: " << normal.x << std::endl;
	std::cout << "left y: " << normal.y << std::endl;
	std::cout << "left z: " << normal.z << std::endl;

	// =======================
	A = { length, 0.0f, width };
	B = { length, 0.0f, 0.0f };
	C = { length, height, 0.0f };
	D = { length, height, width };
	normal = Math::CalcNormal(A, B, C);
	std::cout << "right x: " << normal.x << std::endl;
	std::cout << "right y: " << normal.y << std::endl;
	std::cout << "right z: " << normal.z << std::endl;

	A = { 0.0f, height, width };
	B = { length, height, width };
	C = { length, height, 0.0f };
	D = { 0.0f, height, 0.0f };
	normal = Math::CalcNormal(A, B, C);
	std::cout << "top x: " << normal.x << std::endl;
	std::cout << "top y: " << normal.y << std::endl;
	std::cout << "top z: " << normal.z << std::endl;

	A = { 0.0f, 0.0f, 0.0f };
	B = { length, 0.0f, 0.0f };
	C = { length, 0.0f, width };
	D = { 0.0f, 0.0f, width };
	normal = Math::CalcNormal(A, B, C);
	std::cout << "bottom x: " << normal.x << std::endl;
	std::cout << "bottom y: " << normal.y << std::endl;
	std::cout << "bottom z: " << normal.z << std::endl;

}

Cube::~Cube()
{
	if (texFront != 0) {
		glDeleteTextures(1, &texFront);
		texFront = 0;
	}

	if (texBack != 0) {
		glDeleteTextures(1, &texBack);
		texBack = 0;
	}

	if (texTop != 0) {
		glDeleteTextures(1, &texTop);
		texTop = 0;
	}

	if (texBottom != 0) {
		glDeleteTextures(1, &texBottom);
		texBottom = 0;
	}

	if (texLeft != 0) {
		glDeleteTextures(1, &texLeft);
		texLeft = 0;
	}

	if (texRight != 0) {
		glDeleteTextures(1, &texRight);
		texRight = 0;
	}
}
;

void Cube::ClearTextures() {
	if (texFront != 0) {
		glDeleteTextures(1, &texFront);
		texFront = 0;
	}

	if (texBack != 0) {
		glDeleteTextures(1, &texBack);
		texBack = 0;
	}

	if (texTop != 0) {
		glDeleteTextures(1, &texTop);
		texTop = 0;
	}

	if (texBottom != 0) {
		glDeleteTextures(1, &texBottom);
		texBottom = 0;
	}

	if (texLeft != 0) {
		glDeleteTextures(1, &texLeft);
		texLeft = 0;
	}

	if (texRight != 0) {
		glDeleteTextures(1, &texRight);
		texRight = 0;
	}
}

void Cube::Draw() {

	glPushMatrix();

	//  glColor3f(r, g, b);
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

	glBindTexture(GL_TEXTURE_2D, texBack);
	glBegin(GL_QUADS);
	// back (-Z)
	Math::Vec3 A = { 0.0f, height, 0.0f };
	Math::Vec3 B = { 0.0f, 0.0f, 0.0f };
	Math::Vec3 C = { length, 0.0f, 0.0f };
	Math::Vec3 D = { length, height, 0.0f };
	Math::Vec3 normal = Math::CalcNormal(D, C, B);
	glNormal3f(normal.x, normal.y, normal.z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(B.x, B.y, B.z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(C.x, C.y, C.z);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(D.x, D.y, D.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texFront);
	glBegin(GL_QUADS);
	// front (+Z)
	A = { 0.0f, height, width };
	B = { 0.0f, 0.0f, width };
	C = { length, 0.0f, width };
	D = { length, height, width };
	normal = Math::CalcNormal(A, B, C);
	glNormal3f(normal.x, normal.y, normal.z);
	
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);
	
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(B.x, B.y, B.z);
	
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(C.x, C.y, C.z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(D.x, D.y, D.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texLeft);
	glBegin(GL_QUADS);
	// left (-X)
	A = { 0.0f, height, 0.0f };
	B = { 0.0f, 0.0f, 0.0f };
	C = { 0.0f, 0.0f, width };
	D = { 0.0f, height, width };
	normal = Math::CalcNormal(A, B, C);
	glNormal3f(normal.x, normal.y, normal.z);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(B.x, B.y, B.z);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(C.x, C.y, C.z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(D.x, D.y, D.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texRight);
	glBegin(GL_QUADS);
	// right (+X)
	A = { length, height, width };
	B = { length, 0.0f, width };
	C = { length, 0.0f, 0.0f };
	D = { length, height, 0.0f };
	normal = Math::CalcNormal(A, B, C);
	glNormal3f(normal.x, normal.y, normal.z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(B.x, B.y, B.z);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(C.x, C.y, C.z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(D.x, D.y, D.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texTop);
	glBegin(GL_QUADS);
	// top (+Y)
	A = { 0.0f, height, 0.0f };
	B = { 0.0f, height, width };
	C = { length, height, width };
	D = { length, height, 0.0f };
	normal = Math::CalcNormal(A, B, C);
	glNormal3f(normal.x, normal.y, normal.z);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(B.x, B.y, B.z);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(C.x, C.y, C.z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(D.x, D.y, D.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texBottom);
	glBegin(GL_QUADS);
	// bottom (-Y)
	A = { 0.0f, 0.0f, width };
	B = { 0.0f, 0.0f, 0.0f };
	C = { length, 0.0f, 0.0f };
	D = { length, 0.0f, width };
	normal = Math::CalcNormal(A, B, C);
	glNormal3f(normal.x, normal.y, normal.z);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(B.x, B.y, B.z);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(C.x, C.y, C.z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(D.x, D.y, D.z);
	glEnd();

	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
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
	color[0] = red;
	color[1] = green;
	color[2] = blue;
}

void Cube::SetExpandable(bool ex)
{
	isExpandable = ex;
}

void Cube::SetAllTextures(GLuint tex) {
	texFront = tex;
	texBack = tex;
	texTop = tex;
	texBottom = tex;
	texLeft = tex;
	texRight = tex;
}

void Cube::SetFrontTexture(GLuint front) {
	texFront = front;
}

void Cube::SetBackTexture(GLuint back) {
	texBack = back;
}

void Cube::SetTopTexture(GLuint top) {
	texTop = top;
}

void Cube::SetBottomTexture(GLuint bottom) {
	texBottom = bottom;
}

void Cube::SetLeftTexture(GLuint left) {
	texLeft = left;
}

void Cube::SetRightTexture(GLuint right) {
	texRight = right;
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
