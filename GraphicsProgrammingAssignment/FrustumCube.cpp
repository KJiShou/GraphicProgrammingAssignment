#include "pch.h"
#include "FrustumCube.h"

FrustumCube::FrustumCube(
	float topLength, 
	float topDepth, 
	float topOffsetX, 
	float topOffsetZ, 
	float bottomLength, 
	float bottomDepth, 
	float height,
	float r, 
	float g, 
	float b
):
	topLength(topLength),
	topDepth(topDepth),
	topOffsetX(topOffsetX),
	topOffsetZ(topOffsetZ),
	bottomLength(bottomLength),
	bottomDepth(bottomDepth),
	height(height),
	r(r),
	g(g),
	b(b)
{ 
	color[0] = r;
	color[1] = g;
	color[2] = b;

	centerX = bottomLength * 0.5f;
	centerY = height * 0.5f;
	centerZ = bottomDepth * 0.5f;
}

FrustumCube::~FrustumCube()
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

void FrustumCube::ClearTextures() {
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

void FrustumCube::Draw() {

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

	GLfloat redColor[] = { 1.0f, 0.0f, 0.0f };
	GLfloat greenColor[] = { 0.0f, 1.0f, 0.0f };
	GLfloat blueColor[] = { 0.0f, 0.0f, 1.0f };
	GLfloat yellowColor[] = { 1.0f, 0.984f, 0.0f };
	GLfloat whiteColor[] = { 1.0f, 1.0f, 1.0f };
	GLfloat blackColor[] = { 0.0f, 0.0f, 0.0f };
	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat orangeColor[] = { 1.0f, 0.95f, 0.0f };
	GLfloat orangeColor2[] = { 1.0f, 0.60f, 0.0f };;

	float uScale = topLength / bottomLength;
	float uOffset = (1.0f - uScale) * 0.5f;

	Math::Vec3 A = { 0.0f + topOffsetX, height, topDepth + topOffsetZ };
	Math::Vec3 B = { 0.0f, 0.0f, bottomDepth };
	Math::Vec3 C = { bottomLength, 0.0f, bottomDepth };
	Math::Vec3 D = { topLength + topOffsetX, height, topDepth + topOffsetZ };
	Math::Vec3 normal = Math::CalcNormal(A, B, C);
	glNormal3f(normal.x, normal.y, normal.z);
	glBindTexture(GL_TEXTURE_2D, texFront);
	// front (+z)
	glBegin(GL_QUADS);

	glTexCoord2f(uOffset, 1.0f);
	glVertex3f(A.x, A.y, A.z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(B.x, B.y, B.z);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(C.x, C.y, C.z);

	glTexCoord2f(uOffset + uScale, 1.0f);
	glVertex3f(D.x, D.y, D.z);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texBack);
	A = { topLength + topOffsetX , height, 0.0f + topOffsetZ };
	B = { bottomLength, 0.0f, 0.0f };
	C = { 0.0f, 0.0f, 0.0f };
	D = { 0.0f + topOffsetX, height, 0.0f + topOffsetZ};
	
	normal = Math::CalcNormal(A, B, C);
	glNormal3f(normal.x, normal.y, normal.z);
	// back (-z)
	glBegin(GL_QUADS);

	glTexCoord2f(uOffset, 1.0f);
	glVertex3f(A.x, A.y, A.z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(B.x, B.y, B.z);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(C.x, C.y, C.z);

	glTexCoord2f(uOffset + uScale, 1.0f);
	glVertex3f(D.x, D.y, D.z);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texTop);
	A = { 0.0f + topOffsetX, height, 0.0f + topOffsetZ };
	B = { 0.0f + topOffsetX, height, topDepth + topOffsetZ };
	C = { topLength + topOffsetX, height, topDepth + topOffsetZ };
	D = { topLength + topOffsetX, height, 0.0f + topOffsetZ };
	normal = Math::CalcNormal(A, B, C);
	glNormal3f(normal.x, normal.y, normal.z);
	// top (+y)
	glBegin(GL_QUADS);

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
	A = { 0.0f, 0.0f, bottomDepth };
	B = { 0.0f, 0.0f, 0.0f };
	C = { bottomLength , 0.0f, 0.0f };
	D = { bottomLength, 0.0f, bottomDepth };
	normal = Math::CalcNormal(A, B, C);
	glNormal3f(normal.x, normal.y, normal.z);
	// bottom (-y)
	glBegin(GL_QUADS);

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
	A = { 0.0f + topOffsetX, height, 0.0f + topOffsetZ };
	B = { 0.0f, 0.0f, 0.0f };
	C = { 0.0f, 0.0f, bottomDepth };
	D = { 0.0f + topOffsetX, height, topDepth + topOffsetZ };
	normal = Math::CalcNormal(A, B, C);
	glNormal3f(normal.x, normal.y, normal.z);
	// left (-x)
	glBegin(GL_QUADS);

	glTexCoord2f(uOffset, 1.0f);
	glVertex3f(A.x, A.y, A.z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(B.x, B.y, B.z);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(C.x, C.y, C.z);

	glTexCoord2f(uOffset + uScale, 1.0f);
	glVertex3f(D.x, D.y, D.z);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texRight);
	A = { topLength + topOffsetX, height, topDepth + topOffsetZ };
	B = { bottomLength, 0.0f, bottomDepth };
	C = { bottomLength, 0.0f, 0.0f };
	D = { topLength + topOffsetX, height, 0.0f + topOffsetZ };
	normal = Math::CalcNormal(A, B, C);
	glNormal3f(normal.x, normal.y, normal.z);
	// right (+x)
	glBegin(GL_QUADS);

	glTexCoord2f(uOffset, 1.0f);
	glVertex3f(A.x, A.y, A.z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(B.x, B.y, B.z);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(C.x, C.y, C.z);

	glTexCoord2f(uOffset + uScale, 1.0f);
	glVertex3f(D.x, D.y, D.z);

	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void FrustumCube::Translate(float transX, float transY, float transZ) {
	this->transX = transX;
	this->transY = transY;
	this->transZ = transZ;
}

void FrustumCube::Rotate(float rotX, float rotY, float rotZ, bool isRotateByCenter, float rotPosX, float rotPosY, float rotPosZ) {
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->isRotateByCenter = isRotateByCenter;
	this->rotPosX = rotPosX;
	this->rotPosY = rotPosY;
	this->rotPosZ = rotPosZ;
}

void FrustumCube::Scale(float scaleX, float scaleY, float scaleZ) {
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
}

// ======================
// Setters
// ======================
void FrustumCube::SetTopLength(float l) {
	topLength = l;
}
void FrustumCube::SetTopDepth(float d) {
	topDepth = d;
}
void FrustumCube::SetBottomLength(float l) {
	bottomLength = l;
	centerX = bottomLength * 0.5f;
}
void FrustumCube::SetBottomDepth(float d) {
	bottomDepth = d;
	centerZ = bottomDepth * 0.5f;
}
void FrustumCube::SetTopOffsetX(float x) {
	topOffsetX = x;
}
void FrustumCube::SetTopOffsetZ(float z) {
	topOffsetZ = z;
}
void FrustumCube::SetHeight(float h) {
	height = h;
	centerY = height * 0.5f;
}
void FrustumCube::SetColor(const std::array<float, 3>& c) {
	color[0] = c[0];
	color[1] = c[1];
	color[2] = c[2];
}
void FrustumCube::SetColor(float red, float green, float blue)
{
	color[0] = red;
	color[1] = green;
	color[2] = blue;
}

void FrustumCube::SetExpandable(bool ex)
{
	isExpandable = ex;
}

void FrustumCube::SetAllTextures(GLuint tex) {
	texFront = tex;
	texBack = tex;
	texTop = tex;
	texBottom = tex;
	texLeft = tex;
	texRight = tex;
}

void FrustumCube::SetFrontTexture(GLuint front) {
	texFront = front;
}

void FrustumCube::SetBackTexture(GLuint back) {
	texBack = back;
}

void FrustumCube::SetTopTexture(GLuint top) {
	texTop = top;
}

void FrustumCube::SetBottomTexture(GLuint bottom) {
	texBottom = bottom;
}

void FrustumCube::SetLeftTexture(GLuint left) {
	texLeft = left;
}

void FrustumCube::SetRightTexture(GLuint right) {
	texRight = right;
}

// ======================
// Getters
// ======================

// size
float FrustumCube::GetTopLength() const { return topLength; }
float FrustumCube::GetTopDepth()  const { return topDepth; }
float FrustumCube::GetBottomLength()  const { return bottomLength; }
float FrustumCube::GetBottomDepth()  const { return bottomDepth; }
float FrustumCube::GetTopOffsetX()  const { return topOffsetX; }
float FrustumCube::GetTopOffsetZ()  const { return topOffsetZ; }
float FrustumCube::GetHeight() const { return height; }

// color
float FrustumCube::GetR() const { return r; }
float FrustumCube::GetG() const { return g; }
float FrustumCube::GetB() const { return b; }
std::array<float, 3> FrustumCube::GetColor() const {
	return { color[0], color[1], color[2] };
}
const float* FrustumCube::GetColorPtr() const {
	return color;
}

// translate
float FrustumCube::GetTransX() const { return transX; }
float FrustumCube::GetTransY() const { return transY; }
float FrustumCube::GetTransZ() const { return transZ; }

// rotate
float FrustumCube::GetRotX() const { return rotX; }
float FrustumCube::GetRotY() const { return rotY; }
float FrustumCube::GetRotZ() const { return rotZ; }
bool  FrustumCube::GetIsRotateByCenter() const { return isRotateByCenter; }

// scale
float FrustumCube::GetScaleX() const { return scaleX; }
float FrustumCube::GetScaleY() const { return scaleY; }
float FrustumCube::GetScaleZ() const { return scaleZ; }

// center
float FrustumCube::GetCenterX() const { return centerX; }
float FrustumCube::GetCenterY() const { return centerY; }
float FrustumCube::GetCenterZ() const { return centerZ; }

// rotate point
float FrustumCube::GetRotPosX() const { return rotPosX; }
float FrustumCube::GetRotPosY() const { return rotPosY; }
float FrustumCube::GetRotPosZ() const { return rotPosZ; }

// expand in two way
bool FrustumCube::GetIsExpandable() const { return isExpandable; }

