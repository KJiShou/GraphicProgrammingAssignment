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
	float innerRadius;
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
	std::string topTex;
	std::string bottomTex;
	std::string bodyTex;
	bool isRepeat;
	bool isSpecular;
	float shininess;
	CylinderData()
		: topTex(""), bottomTex(""), bodyTex(""), isSpecular(true),
		isRepeat(true), shininess(50.0f)
	{}
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
	std::string sphereTex;
	bool isRepeat;
	bool isSpecular;
	float shininess;
	SphereData()
		: sphereTex(""), isRepeat(true), isSpecular(true), shininess(50.0f)
	{}
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
	std::string frontTex;
	std::string backTex;
	std::string topTex;
	std::string bottomTex;
	std::string leftTex;
	std::string rightTex;
	bool isRepeat;
	bool isSpecular;
	float shininess;
	CubeData()
		: frontTex(""), backTex(""), topTex(""),
		bottomTex(""), leftTex(""), rightTex(""),
		isRepeat(true) , isSpecular(true), shininess(50.0f)
	{}
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
	std::string frontTex;
	std::string backTex;
	std::string bottomTex;
	std::string leftTex;
	std::string rightTex;
	bool isRepeat;
	bool isSpecular;
	float shininess;
	PyramidData()
		: frontTex(""), backTex(""),
		bottomTex(""), leftTex(""), rightTex(""),
		isRepeat(true), isSpecular(true), shininess(50.0f)
	{}
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
	std::string frontTex;
	std::string backTex;
	std::string topTex;
	std::string bottomTex;
	std::string leftTex;
	std::string rightTex;
	bool isRepeat;
	bool isSpecular;
	float shininess;
	FrustumCubeData()
		: frontTex(""), backTex(""), topTex(""),
		bottomTex(""), leftTex(""), rightTex(""),
		isRepeat(true), isSpecular(true), shininess(50.0f)
	{
	}
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
	bool isRepeat;
	bool isSpecular;
	float shininess;
};

class Object
{
private:
	//GLuint defaultTex;
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

	GLuint LoadTexture(const std::string& filename, bool isRepeat);
};

