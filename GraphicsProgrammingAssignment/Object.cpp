#include "pch.h"
#include "Object.h"

Object::Object(std::string fName) {
	fileName = fName;
	ReadData(true);
}

Object::~Object() = default;


void Object::Translate(float x, float y, float z) {
	transX = x;
	transY = y;
	transZ = z;
}
void Object::Rotate(float x, float y, float z, float pivotX, float pivotY , float pivotZ ) {
	rotX = x;
	rotY = y;
	rotZ = z;
	rotPivotX = pivotX;
	rotPivotY = pivotY;
	rotPivotZ = pivotZ;
}
void Object::Scale(float x, float y, float z) {
	scaleX = x;
	scaleY = y;
	scaleZ = z;
}

void Object::ReadData(bool firstRun) {

	glLoadIdentity();

	cylindersData.clear();
	spheresData.clear();
	cubesData.clear();
	pyramidsData.clear();

	// open json file
	std::ifstream file(fileName);
	// std::cout << "Opening {" << fileName << "} JSON file!" << std::endl;
	if (!file.is_open()) {
		std::cout << "Failed to open {" << fileName <<  "} JSON file!" << std::endl;
		return;
	}

	try {
		file >> j;
	}
	catch (nlohmann::json::parse_error& e) {
		std::cout << "JSON parse error: " << e.what() << std::endl;
		return;
	}

	for (auto& jc : j["cylinders"]) {
		CylinderData c;
		c.baseRadius = jc["baseRadius"];
		c.topRadius = jc["topRadius"];
		c.height = jc["height"];
		c.slices = jc["slices"];
		c.stacks = jc["stacks"];
		if (jc["style"] == "GLU_LINE")
		{
			c.style = GLU_LINE;
		}
		else if (jc["style"] == "GLU_FILL")
		{
			c.style = GLU_FILL;
		}
		c.isClose = jc["isClose"];
		c.lineWidth = jc["lineWidth"];
		c.r = jc["r"];
		c.g = jc["g"];
		c.b = jc["b"];

		c.transX = jc["transX"];
		c.transY = jc["transY"];
		c.transZ = jc["transZ"];

		c.rotX = jc["rotX"];
		c.rotY = jc["rotY"];
		c.rotZ = jc["rotZ"];

		c.scaleX = jc["scaleX"];
		c.scaleY = jc["scaleY"];
		c.scaleZ = jc["scaleZ"];

		cylindersData.push_back(c);
	}

	for (auto& jc : j["spheres"]) {
		SphereData s;
		s.radius = jc["radius"];
		s.slices = jc["slices"];
		s.stacks = jc["stacks"];
		if (jc["style"] == "GLU_LINE")
		{
			s.style = GLU_LINE;
		}
		else if (jc["style"] == "GLU_FILL")
		{
			s.style = GLU_FILL;
		}
		s.lineWidth = jc["lineWidth"];
		s.r = jc["r"];
		s.g = jc["g"];
		s.b = jc["b"];

		s.transX = jc["transX"];
		s.transY = jc["transY"];
		s.transZ = jc["transZ"];

		s.rotX = jc["rotX"];
		s.rotY = jc["rotY"];
		s.rotZ = jc["rotZ"];

		s.scaleX = jc["scaleX"];
		s.scaleY = jc["scaleY"];
		s.scaleZ = jc["scaleZ"];

		spheresData.push_back(s);
	}

	for (auto& jc : j["cubes"]) {
		CubeData c;
		c.length = jc["length"];
		c.width = jc["width"];
		c.height = jc["height"];
		c.r = jc["r"];
		c.g = jc["g"];
		c.b = jc["b"];

		c.transX = jc["transX"];
		c.transY = jc["transY"];
		c.transZ = jc["transZ"];

		c.rotX = jc["rotX"];
		c.rotY = jc["rotY"];
		c.rotZ = jc["rotZ"];

		c.scaleX = jc["scaleX"];
		c.scaleY = jc["scaleY"];
		c.scaleZ = jc["scaleZ"];

		c.isExpandable = jc["isExpandable"];

		cubesData.push_back(c);
	}

	for (auto& jc : j["pyramids"]) {
		PyramidData p;
		p.length = jc["length"];
		p.width = jc["width"];
		p.height = jc["height"];
		p.r = jc["r"];
		p.g = jc["g"];
		p.b = jc["b"];

		p.transX = jc["transX"];
		p.transY = jc["transY"];
		p.transZ = jc["transZ"];

		p.rotX = jc["rotX"];
		p.rotY = jc["rotY"];
		p.rotZ = jc["rotZ"];

		p.scaleX = jc["scaleX"];
		p.scaleY = jc["scaleY"];
		p.scaleZ = jc["scaleZ"];

		pyramidsData.push_back(p);
	}

	// When start program
	if (firstRun)
	{
		size_t i = 0;
		for (auto& data : cylindersData)
		{
			cylinders.push_back(std::make_unique<Cylinder>(data.baseRadius, data.topRadius, data.height, data.slices, data.stacks, data.style, data.isClose, data.lineWidth, data.r, data.g, data.b));
			cylinders[i]->Translate(data.transX, data.transY, data.transZ);
			cylinders[i]->Rotate(data.rotX, data.rotY, data.rotZ, false, 0.0f, 0.0f, 0.0f);
			cylinders[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			i++;
		}
		i = 0;
		for (auto& data : spheresData)
		{
			spheres.push_back(std::make_unique<Sphere>(data.radius, data.slices, data.stacks, data.style, data.lineWidth, data.r, data.g, data.b));
			spheres[i]->Translate(data.transX, data.transY, data.transZ);
			spheres[i]->Rotate(data.rotX, data.rotY, data.rotZ);
			spheres[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			i++;
		}
		i = 0;
		for (auto& data : cubesData)
		{
			cubes.push_back(std::make_unique<Cube>(data.length, data.width, data.height, data.r, data.g, data.b));
			cubes[i]->Translate(data.transX, data.transY, data.transZ);
			cubes[i]->Rotate(data.rotX, data.rotY, data.rotZ);
			cubes[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			cubes[i]->SetExpandable(data.isExpandable);
			i++;
		}
		i = 0;
		for (auto& data : pyramidsData)
		{
			pyramids.push_back(std::make_unique<Pyramid>(data.length, data.width, data.height, data.r, data.g, data.b));
			pyramids[i]->Translate(data.transX, data.transY, data.transZ);
			pyramids[i]->Rotate(data.rotX, data.rotY, data.rotZ);
			pyramids[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			i++;
		}
	}
	else
	{
		// Press Enter can refresh data, able to modify the 3D shape in runtime 
		for (size_t i = 0; i < cylinders.size() && i < cylindersData.size(); i++) {
			cylinders[i]->SetBaseRadius(cylindersData[i].baseRadius);
			cylinders[i]->SetTopRadius(cylindersData[i].topRadius);
			cylinders[i]->SetHeight(cylindersData[i].height);
			cylinders[i]->SetSlices(cylindersData[i].slices);
			cylinders[i]->SetStacks(cylindersData[i].stacks);
			cylinders[i]->SetStyle(cylindersData[i].style);
			cylinders[i]->SetIsClose(cylindersData[i].isClose);
			cylinders[i]->SetLineWidth(cylindersData[i].lineWidth);
			cylinders[i]->SetColor(cylindersData[i].r, cylindersData[i].g, cylindersData[i].b);
			cylinders[i]->Translate(cylindersData[i].transX, cylindersData[i].transY, cylindersData[i].transZ);
			// Rotate around the base so increasing height does not move the positioned base
			cylinders[i]->Rotate(cylindersData[i].rotX, cylindersData[i].rotY, cylindersData[i].rotZ, false, 0.0f, 0.0f, 0.0f);
			cylinders[i]->Scale(cylindersData[i].scaleX, cylindersData[i].scaleY, cylindersData[i].scaleZ);
		}

		for (size_t i = 0; i < spheres.size() && i < spheresData.size(); i++)
		{
			spheres[i]->SetRadius(spheresData[i].radius);
			spheres[i]->SetSlices(spheresData[i].slices);
			spheres[i]->SetStacks(spheresData[i].stacks);
			spheres[i]->SetStyle(spheresData[i].style);
			spheres[i]->SetLineWidth(spheresData[i].lineWidth);
			spheres[i]->SetColor(spheresData[i].r, spheresData[i].g, spheresData[i].b);
			spheres[i]->Translate(spheresData[i].transX, spheresData[i].transY, spheresData[i].transZ);
			spheres[i]->Rotate(spheresData[i].rotX, spheresData[i].rotY, spheresData[i].rotZ);
			spheres[i]->Scale(spheresData[i].scaleX, spheresData[i].scaleY, spheresData[i].scaleZ);
		}

		for (size_t i = 0; i < cubes.size() && i < cubesData.size(); i++)
		{
			cubes[i]->SetLength(cubesData[i].length);
			cubes[i]->SetWidth(cubesData[i].width);
			cubes[i]->SetHeight(cubesData[i].height);
			cubes[i]->SetColor(cubesData[i].r, cubesData[i].g, cubesData[i].b);
			cubes[i]->Translate(cubesData[i].transX, cubesData[i].transY, cubesData[i].transZ);
			cubes[i]->Rotate(cubesData[i].rotX, cubesData[i].rotY, cubesData[i].rotZ);
			cubes[i]->Scale(cubesData[i].scaleX, cubesData[i].scaleY, cubesData[i].scaleZ);
			cubes[i]->SetExpandable(cubesData[i].isExpandable);
		}

		for (size_t i = 0; i < pyramids.size() && i < pyramidsData.size(); i++)
		{
			pyramids[i]->SetLength(pyramidsData[i].length);
			pyramids[i]->SetWidth(pyramidsData[i].width);
			pyramids[i]->SetHeight(pyramidsData[i].height);
			pyramids[i]->SetColor(pyramidsData[i].r, pyramidsData[i].g, pyramidsData[i].b);
			pyramids[i]->Translate(pyramidsData[i].transX, pyramidsData[i].transY, pyramidsData[i].transZ);
			pyramids[i]->Rotate(pyramidsData[i].rotX, pyramidsData[i].rotY, pyramidsData[i].rotZ);
			pyramids[i]->Scale(pyramidsData[i].scaleX, pyramidsData[i].scaleY, pyramidsData[i].scaleZ);
		}
	}
}

void Object::Draw() {
	glPushMatrix();

	glTranslatef(transX, transY, transZ);

	if (rotPivotX != 0.0f || rotPivotY != 0.0f || rotPivotZ != 0.0f)
	{
		glTranslatef(rotPivotX, rotPivotY, rotPivotZ);
	}

	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotZ, 0, 0, 1);

	if (rotPivotX != 0.0f || rotPivotY != 0.0f || rotPivotZ != 0.0f)
	{
		glTranslatef(-rotPivotX, -rotPivotY, -rotPivotZ);
	}

	glScalef(scaleX, scaleY, scaleZ);

	for (auto& cylinder : cylinders)
	{
		cylinder->Draw();
	}

	for (auto& sphere : spheres)
	{
		sphere->Draw();
	}

	for (auto& cube : cubes)
	{
		cube->Draw();
	}

	for (auto& pyramid : pyramids)
	{
		pyramid->Draw();
	}

	for (Object* o : children) o->Draw();

	glPopMatrix();
}

void Object::ReadData() {
	ReadData(false);
}

void Object::AddChild(Object* o) {
	o->parent = this;
	children.push_back(o);
}
