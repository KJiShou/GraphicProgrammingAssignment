#include "pch.h"
#include "Pyramid.h"
#include "Math.h"

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
	color[0] = r;
	color[1] = g;
	color[2] = b;
	centerX = length * 0.5f;
	centerY = height * 0.5f;
	centerZ = width * 0.5f;
};
Pyramid::~Pyramid() {
	if (texFront != 0) {
		glDeleteTextures(1, &texFront);
		texFront = 0;
	}

	if (texBack != 0) {
		glDeleteTextures(1, &texBack);
		texBack = 0;
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

void Pyramid::ClearTextures() {
	if (texFront != 0) {
		glDeleteTextures(1, &texFront);
		texFront = 0;
	}

	if (texBack != 0) {
		glDeleteTextures(1, &texBack);
		texBack = 0;
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

void Pyramid::Draw() {

	glPushMatrix();

	//glColor3f(r, g, b);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);

	GLfloat noSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	if (isSpecular)
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular),
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0f);
	else
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, noSpecular),
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);

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

	float tilingSize = 1.0f;

	float tx = isRepeat ? (length / tilingSize) : 1.0f;
	float tz = isRepeat ? (width / tilingSize) : 1.0f;
	float ty = isRepeat ? (height / tilingSize) : 1.0f;

	Math::Vec3 apex = { centerX, height, centerZ };
	Math::Vec3 v0 = { 0.0f, 0.0f, 0.0f };       // back-left
	Math::Vec3 v1 = { length, 0.0f, 0.0f };     // back-right
	Math::Vec3 v2 = { length, 0.0f, width };    // front-right
	Math::Vec3 v3 = { 0.0f, 0.0f, width };      // front-left

	// base (facing downward)
	glBindTexture(GL_TEXTURE_2D, texBottom);
	glBegin(GL_QUADS);
	Math::Vec3 normal = Math::CalcNormal(v0, v1, v2);
	glNormal3f(normal.x, normal.y, normal.z);

	glTexCoord2f(0.0f, tz); glVertex3f(v3.x, v3.y, v3.z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(v0.x, v0.y, v0.z);
	glTexCoord2f(tx, 0.0f); glVertex3f(v1.x, v1.y, v1.z);
	glTexCoord2f(tx, tz);   glVertex3f(v2.x, v2.y, v2.z);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texFront);
	glBegin(GL_TRIANGLES);
	// front (+Z)
	normal = Math::CalcNormal(v3, v2, apex);
	glNormal3f(normal.x, normal.y, normal.z);

	glTexCoord2f(tx * 0.5f, ty);   glVertex3f(apex.x, apex.y, apex.z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(v3.x, v3.y, v3.z);
	glTexCoord2f(tx, 0.0f); glVertex3f(v2.x, v2.y, v2.z);
	
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texBack);
	glBegin(GL_TRIANGLES);
	// back (-Z)
	normal = Math::CalcNormal(v1, v0, apex);
	glNormal3f(normal.x, normal.y, normal.z);

	glTexCoord2f(tx * 0.5f, ty);   glVertex3f(apex.x, apex.y, apex.z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x, v1.y, v1.z);
	glTexCoord2f(tx, 0.0f); glVertex3f(v0.x, v0.y, v0.z);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texRight);
	glBegin(GL_TRIANGLES);
	// right (+X)
	normal = Math::CalcNormal(v2, v1, apex);
	glNormal3f(normal.x, normal.y, normal.z);

	glTexCoord2f(tz * 0.5f, ty);   glVertex3f(apex.x, apex.y, apex.z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(v2.x, v2.y, v2.z);
	glTexCoord2f(tz, 0.0f); glVertex3f(v1.x, v1.y, v1.z);
	
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texLeft);
	glBegin(GL_TRIANGLES);
	// left (-X)
	normal = Math::CalcNormal(v0, v3, apex);
	glNormal3f(normal.x, normal.y, normal.z);

	glTexCoord2f(tz * 0.5f, ty);   glVertex3f(apex.x, apex.y, apex.z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(v0.x, v0.y, v0.z);
	glTexCoord2f(tz, 0.0f); glVertex3f(v3.x, v3.y, v3.z);
	glEnd();

	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
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

void Pyramid::SetColor(const std::array<float, 3>& c) {
	color[0] = c[0];
	color[1] = c[1];
	color[2] = c[2];
}
void Pyramid::SetColor(float red, float green, float blue)
{
	color[0] = red;
	color[1] = green;
	color[2] = blue;
}

void Pyramid::SetAllTextures(GLuint tex) {
	texFront = tex;
	texBack = tex;
	texBottom = tex;
	texLeft = tex;
	texRight = tex;
}

void Pyramid::SetFrontTexture(GLuint front) {
	texFront = front;
}

void Pyramid::SetBackTexture(GLuint back) {
	texBack = back;
}

void Pyramid::SetBottomTexture(GLuint bottom) {
	texBottom = bottom;
}

void Pyramid::SetLeftTexture(GLuint left) {
	texLeft = left;
}

void Pyramid::SetRightTexture(GLuint right) {
	texRight = right;
}

void Pyramid::SetIsRepeat(bool r) {
	isRepeat = r;
}

void Pyramid::SetIsSpecular(bool s) {
	isSpecular = s;
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
std::array<float, 3> Pyramid::GetColor() const {
	return { color[0], color[1], color[2] };
}
const float* Pyramid::GetColorPtr() const {
	return color;
}

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
