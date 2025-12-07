#pragma once
class Light
{
public:
	Light(const std::array<float, 3>& ambient,
		const std::array<float, 3>& diffuse,
		const std::array<float, 3>& position,
		GLenum id);

	void Update();
	void Enable();
	void Disable();
	void Move(float x, float y, float z);

	// --- Getters ---
	const std::array<float, 3>& GetAmbient() const;
	const std::array<float, 3>& GetDiffuse() const;
	const std::array<float, 3>& GetPosition() const;
	GLenum GetLightID() const;

	// --- Setters ---
	void SetAmbient(const std::array<float, 3>& ambient);
	void SetAmbient(float x, float y, float z);

	void SetDiffuse(const std::array<float, 3>& diffuse);
	void SetDiffuse(float x, float y, float z);

	void SetPosition(const std::array<float, 3>& position);
	void SetPosition(float x, float y, float z);

private:
	std::array<float, 3> ambientLight;
	std::array<float, 3> diffuseLight;
	std::array<float, 3> diffuseLightPos;
	GLenum lightID = GL_LIGHT0;
};

