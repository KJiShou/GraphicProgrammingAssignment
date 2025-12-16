#pragma once
#include "pch.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Pyramid.h"
#include "Cube.h"
#include "Tetrahedron.h"
#include "FrustumCube.h"
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
	bool isExpandable;
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

struct TetrahedronData {
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

struct FrustumCubeData {
	float topLength;
	float topDepth;
	float topOffsetX;
	float topOffsetZ;
	float bottomLength;
	float bottomDepth;
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
	bool isExpandable;
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
	float rotPivotX = 0.0f;
	float rotPivotY = 0.0f;
	float rotPivotZ = 0.0f;

	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;

	std::vector<CylinderData> cylindersData;
	std::vector<SphereData> spheresData;
	std::vector<CubeData> cubesData;
	std::vector<PyramidData> pyramidsData;
	std::vector<TetrahedronData> tetrahedronsData;
	std::vector<FrustumCubeData> frustumCubesData;

	std::vector<std::unique_ptr<Cylinder>> cylinders;
	std::vector<std::unique_ptr<Sphere>> spheres;
	std::vector<std::unique_ptr<Cube>> cubes;
	std::vector<std::unique_ptr<Pyramid>> pyramids;
	std::vector<std::unique_ptr<Tetrahedron>> tetrahedrons;
	std::vector<std::unique_ptr<FrustumCube>> frustumCubes;

	Object* parent = nullptr;
	std::vector<Object*> children;
	void ReadData(bool firstRun);

public:
	Object(std::string fileName);
	virtual ~Object();

	void Draw();

	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z, float pivotX = 0.0f, float pivotY = 0.0f, float pivotZ = 0.0f);
	void Scale(float x, float y, float z);
	void ReadData();

	void AddChild(Object* o);
};

