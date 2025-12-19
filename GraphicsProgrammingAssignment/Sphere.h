#pragma once
class Sphere
{
public:
	Sphere(float radius, int slices, int stacks, GLenum style, float lineWidth, float r, float g, float b);
	~Sphere();
	void Draw();
	void Translate(float transX, float transY, float transZ);
	void Rotate(float rotX, float rotY, float rotZ, bool isRotateByCenter = true, float rotPosX = 0.0f, float rotPosY = 0.0f, float rotPosZ = 0.0f);
	void Scale(float scaleX, float scaleY, float scaleZ);

	void ClearTextures();

	// ======================
	// Setters
	// ======================
	void SetRadius(float r);
	void SetLineWidth(float l);
	void SetSlices(int s);
	void SetStacks(int s);
	void SetStyle(GLenum s);

	void SetColor(float red, float green, float blue);
	void SetColor(const std::array<float, 3>& c);

	void SetSphereTexture(GLuint tex);

	void SetIsSpecular(bool s);
	void SetShininess(float s);

	// ======================
	// Getters
	// ======================
	//GLUquadricObj* GetObj() const;
	GLenum GetStyle() const;

	// size
	float GetRadius() const;
	float GetLineWidth() const;
	int GetSlices() const;
	int GetStacks() const;

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
private:
	GLUquadricObj* obj = nullptr;
	GLenum style;

	// texture
	GLuint tex = 0;

	// size
	float radius;
	float lineWidth;
	int slices;
	int stacks;

	// color
	float r;
	float g;
	float b;
	float color[3];

	// translate
	float transX = 0.0f;
	float transY = 0.0f;
	float transZ = 0.0f;

	// rotate
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;
	bool isRotateByCenter = true;

	// scale
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;

	// center point
	float centerX = 0.0f;
	float centerY = 0.0f;
	float centerZ = 0.0f;

	// rotate point
	float rotPosX = 0.0f;
	float rotPosY = 0.0f;
	float rotPosZ = 0.0f;

	bool isSpecular = false;
	float shininess = 50.0f;
};

