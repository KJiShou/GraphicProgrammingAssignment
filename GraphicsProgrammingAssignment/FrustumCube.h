#pragma once
class FrustumCube
{
public:
	FrustumCube(float topLength, float topDepth, float topOffsetX, float topOffsetZ, float bottomLength, float bottomDepth, float height, float r, float g, float b);
	
	~FrustumCube();

	void Draw();
	void Translate(float x, float y, float z);
	void Rotate(float rotX, float rotY, float rotZ, bool isRotateByCenter = true, float rotPosX = 0.0f, float rotPosY = 0.0f, float rotPosZ = 0.0f);
	void Scale(float scaleX, float scaleY, float scaleZ);

	void ClearTextures();

	// ======================
	// Setters
	// ======================
	void SetTopLength(float l);
	void SetTopDepth(float d);
	void SetBottomLength(float l);
	void SetBottomDepth(float d);
	void SetTopOffsetX(float x);
	void SetTopOffsetZ(float y);
	void SetHeight(float height);

	void SetColor(float red, float green, float blue);
	void SetColor(const std::array<float, 3>& c);

	void SetExpandable(bool ex);

	void SetAllTextures(GLuint tex);
	void SetFrontTexture(GLuint front);
	void SetBackTexture(GLuint back);
	void SetTopTexture(GLuint top);
	void SetBottomTexture(GLuint bottom);
	void SetLeftTexture(GLuint left);
	void SetRightTexture(GLuint right);

	// ======================
	// Getters
	// ======================
	// size
	float GetTopLength() const;
	float GetTopDepth() const;
	float GetBottomLength() const;
	float GetBottomDepth() const;
	float GetTopOffsetX() const;
	float GetTopOffsetZ() const;
	float GetHeight() const;

	// color
	float GetR() const;
	float GetG() const;
	float GetB() const;
	std::array<float, 3> GetColor() const;
	const float* GetColorPtr() const;

	// translate
	float GetTransX() const;
	float GetTransY() const;
	float GetTransZ() const;

	// rotate
	float GetRotX() const;
	float GetRotY() const;
	float GetRotZ() const;
	bool  GetIsRotateByCenter() const;

	// scale
	float GetScaleX() const;
	float GetScaleY() const;
	float GetScaleZ() const;

	// center
	float GetCenterX() const;
	float GetCenterY() const;
	float GetCenterZ() const;

	// rotate point
	float GetRotPosX() const;
	float GetRotPosY() const;
	float GetRotPosZ() const;

	bool GetIsExpandable() const;

private:
	// textures
	GLuint texFront = 0;
	GLuint texBack = 0;
	GLuint texTop = 0;
	GLuint texBottom = 0;
	GLuint texLeft = 0;
	GLuint texRight = 0;

	// size
	float topLength;
	float topDepth;
	float topOffsetX;
	float topOffsetZ;
	float bottomLength;
	float bottomDepth;
	float height;

	// color
	float r;
	float g;
	float b;
	float color[3];

	// center point
	float centerX = 0.0f;
	float centerY = 0.0f;
	float centerZ = 0.0f;

	// rotate
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;
	bool isRotateByCenter = true;

	// translate
	float transX = 0.0f;
	float transY = 0.0f;
	float transZ = 0.0f;

	// scale
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;

	// rotate point
	float rotPosX = 0.0f;
	float rotPosY = 0.0f;
	float rotPosZ = 0.0f;

	// expand in two way
	bool isExpandable = false;
};

