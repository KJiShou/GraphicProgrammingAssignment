#pragma once
#include "pch.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Pyramid.h"
#include "Cube.h"
struct CylinderData {
	float baseRadius;
	float topRadius;
	float height;
	int slices;
	int stacks;
	GLenum style;
	bool isClose;
	float lineWidth;
	float r;
	float g;
	float b;
	float transX;
	float transY;
	float transZ;
	float rotX;
	float rotY;
	float rotZ;
	float scaleX;
	float scaleY;
	float scaleZ;
};
struct SphereData {
	float radius;
	int slices;
	int stacks;
	GLenum style;
	float lineWidth;
	float r;
	float g;
	float b;
	float transX;
	float transY;
	float transZ;
	float rotX;
	float rotY;
	float rotZ;
	float scaleX;
	float scaleY;
	float scaleZ;
};
struct CubeData {
	float length;
	float width;
	float height;
	float r;
	float g;
	float b;
	float transX;
	float transY;
	float transZ;
	float rotX;
	float rotY;
	float rotZ;
	float scaleX;
	float scaleY;
	float scaleZ;
};
struct PyramidData {
	float length;
	float width;
	float height;
	float r;
	float g;
	float b;
	float transX;
	float transY;
	float transZ;
	float rotX;
	float rotY;
	float rotZ;
	float scaleX;
	float scaleY;
	float scaleZ;
};

class Object
{
private:
	std::string fileName;
	nlohmann::json j;

	float transX = 0.0f;
	float transY = 0.0f;
	float transZ = 0.0f;

	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;

	float scaleX = 0.0f;
	float scaleY = 0.0f;
	float scaleZ = 0.0f;

	std::vector<CylinderData> cylindersData;
	std::vector<SphereData> spheresData;
	std::vector<CubeData> cubesData;
	std::vector<PyramidData> pyramidsData;

	std::vector<std::unique_ptr<Cylinder>> cylinders;
	std::vector<std::unique_ptr<Sphere>> spheres;
	std::vector<std::unique_ptr<Cube>> cubes;
	std::vector<std::unique_ptr<Pyramid>> pyramids;
	void ReadData(bool firstRun);

	bool isPush = false;
public:
	Object(std::string fileName);
	virtual ~Object();
	/*Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;
	Object(Object&&) noexcept = default;
	Object& operator=(Object&&) noexcept = default;*/

	void Draw();

	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);
	void ReadData();
};

