#pragma once
class Light
{
public:
	Light(const std::array<float, 4>& ambient,
		const std::array<float, 4>& diffuse,
		const std::array<float, 4>& position,
		GLenum id);

	void Update();
	void Enable();
	void Disable();
	void Move(float x, float y, float z);

	// --- Getters ---
	const std::array<float, 4>& GetAmbient() const;
	const std::array<float, 4>& GetDiffuse() const;
	const std::array<float, 4>& GetPosition() const;
	GLenum GetLightID() const;

	// --- Setters ---
	void SetAmbient(const std::array<float, 4>& ambient);
	void SetAmbient(float x, float y, float z, float a);

	void SetDiffuse(const std::array<float, 4>& diffuse);
	void SetDiffuse(float x, float y, float z, float a);

	void SetPosition(const std::array<float, 4>& position);
	void SetPosition(float x, float y, float z);

private:
	std::array<float, 4> ambientLight;
	std::array<float, 4> diffuseLight;
	std::array<float, 4> diffuseLightPos;
	GLenum lightID = GL_LIGHT0;
};

