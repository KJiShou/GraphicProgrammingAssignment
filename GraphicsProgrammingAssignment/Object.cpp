#include "pch.h"
#include "Object.h"

Object::Object(std::string fName) {
	fileName = fName;
	ReadData(true);
}

Object::~Object() {
	for (Object* c : children) {
		delete c;
	}

	/*if (defaultTex != 0) {
		glDeleteTextures(1, &defaultTex);
		defaultTex = 0;
	}*/
}


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
	tetrahedronsData.clear();
	frustumCubesData.clear();

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
		CylinderData f;

		// if the key not exist, then use default value to prevent error
		f.baseRadius = jc.value("baseRadius", 1.0f);
		f.topRadius = jc.value("topRadius", 1.0f);
		f.height = jc.value("height", 1.0f);
		f.slices = jc.value("slices", 16);
		f.stacks = jc.value("stacks", 1);
		f.innerRadius = jc.value("innerRadius", 0.0f);

		// style
		std::string styleStr = jc.value("style", "GLU_FILL");
		if (styleStr == "GLU_LINE")
			f.style = GLU_LINE;
		else
			f.style = GLU_FILL;

		f.isClose = jc.value("isClose", false);
		f.lineWidth = jc.value("lineWidth", 1.0f);

		f.r = jc.value("r", 1.0f);
		f.g = jc.value("g", 1.0f);
		f.b = jc.value("b", 1.0f);

		f.transX = jc.value("transX", 0.0f);
		f.transY = jc.value("transY", 0.0f);
		f.transZ = jc.value("transZ", 0.0f);

		f.rotX = jc.value("rotX", 0.0f);
		f.rotY = jc.value("rotY", 0.0f);
		f.rotZ = jc.value("rotZ", 0.0f);

		f.scaleX = jc.value("scaleX", 1.0f);
		f.scaleY = jc.value("scaleY", 1.0f);
		f.scaleZ = jc.value("scaleZ", 1.0f);

		f.isSpecular = jc.value("isSpecular", true);
		f.shininess = jc.value("shininess", 50.0f);

		if (jc.contains("textures") && jc["textures"].is_object()) {
			auto& tex = jc["textures"];

			std::string all = tex.value("all", "");
			if (!all.empty()) {
				f.topTex = all;
				f.bottomTex = all;
				f.bodyTex = all;
			}

			std::string top = tex.value("top", "");
			std::string bottom = tex.value("bottom", "");
			std::string body = tex.value("body", "");

			if (!top.empty())    f.topTex = top;
			if (!bottom.empty()) f.bottomTex = bottom;
			if (!body.empty())   f.bodyTex = body;

			f.isRepeat = tex.value("isRepeat", true);
		}

		cylindersData.push_back(f);
	}

	for (auto& jc : j["spheres"]) {
		SphereData s;

		s.radius = jc.value("radius", 1.0f);
		s.slices = jc.value("slices", 16);
		s.stacks = jc.value("stacks", 16);

		// style
		std::string styleStr = jc.value("style", "GLU_FILL");
		if (styleStr == "GLU_LINE")
			s.style = GLU_LINE;
		else
			s.style = GLU_FILL;

		s.lineWidth = jc.value("lineWidth", 1.0f);

		s.r = jc.value("r", 1.0f);
		s.g = jc.value("g", 1.0f);
		s.b = jc.value("b", 1.0f);

		s.transX = jc.value("transX", 0.0f);
		s.transY = jc.value("transY", 0.0f);
		s.transZ = jc.value("transZ", 0.0f);

		s.rotX = jc.value("rotX", 0.0f);
		s.rotY = jc.value("rotY", 0.0f);
		s.rotZ = jc.value("rotZ", 0.0f);

		s.scaleX = jc.value("scaleX", 1.0f);
		s.scaleY = jc.value("scaleY", 1.0f);
		s.scaleZ = jc.value("scaleZ", 1.0f);

		s.isSpecular = jc.value("isSpecular", true);
		s.shininess = jc.value("shininess", 50.0f);

		if (jc.contains("textures") && jc["textures"].is_object()) {
			auto& tex = jc["textures"];

			std::string all = tex.value("all", "");
			if (!all.empty()) {
				s.sphereTex = all;
			}

			s.isRepeat = tex.value("isRepeat", true);
		}

		spheresData.push_back(s);
	}

	for (auto& jc : j["cubes"]) {
		CubeData c;

		// if the key not exist, then use default value to prevent error
		c.length = jc.value("length", 1.0f);
		c.width = jc.value("width", 1.0f);
		c.height = jc.value("height", 1.0f);

		c.r = jc.value("r", 1.0f);
		c.g = jc.value("g", 1.0f);
		c.b = jc.value("b", 1.0f);

		c.transX = jc.value("transX", 0.0f);
		c.transY = jc.value("transY", 0.0f);
		c.transZ = jc.value("transZ", 0.0f);

		c.rotX = jc.value("rotX", 0.0f);
		c.rotY = jc.value("rotY", 0.0f);
		c.rotZ = jc.value("rotZ", 0.0f);

		c.scaleX = jc.value("scaleX", 1.0f);
		c.scaleY = jc.value("scaleY", 1.0f);
		c.scaleZ = jc.value("scaleZ", 1.0f);

		c.isExpandable = jc.value("isExpandable", true);
		c.isSpecular = jc.value("isSpecular", true);
		c.shininess = jc.value("shininess", 50.0f);

		if (jc.contains("textures") && jc["textures"].is_object()) {
			auto& tex = jc["textures"];

			std::string all = tex.value("all", "");
			if (!all.empty()) {
				c.frontTex = c.backTex = c.topTex =
					c.bottomTex = c.leftTex = c.rightTex = all;
			}

			std::string top = tex.value("top", "");
			std::string bottom = tex.value("bottom", "");
			std::string front = tex.value("front", "");
			std::string back = tex.value("back", "");
			std::string left = tex.value("left", "");
			std::string right = tex.value("right", "");

			if (!top.empty())    c.topTex = top;
			if (!bottom.empty()) c.bottomTex = bottom;
			if (!front.empty())   c.frontTex = front;
			if (!back.empty())   c.backTex = back;
			if (!left.empty())   c.leftTex = left;
			if (!right.empty())   c.rightTex = right;

			c.isRepeat = tex.value("isRepeat", true);
		}

		cubesData.push_back(c);
	}

	for (auto& jc : j["pyramids"]) {
		PyramidData p;
		
		p.length = jc.value("length", 1.0f);
		p.width = jc.value("width", 1.0f);
		p.height = jc.value("height", 1.0f);

		p.r = jc.value("r", 1.0f);
		p.g = jc.value("g", 1.0f);
		p.b = jc.value("b", 1.0f);

		p.transX = jc.value("transX", 0.0f);
		p.transY = jc.value("transY", 0.0f);
		p.transZ = jc.value("transZ", 0.0f);

		p.rotX = jc.value("rotX", 0.0f);
		p.rotY = jc.value("rotY", 0.0f);
		p.rotZ = jc.value("rotZ", 0.0f);

		p.scaleX = jc.value("scaleX", 1.0f);
		p.scaleY = jc.value("scaleY", 1.0f);
		p.scaleZ = jc.value("scaleZ", 1.0f);

		p.isSpecular = jc.value("isSpecular", true);
		p.shininess = jc.value("shininess", 50.0f);

		std::string all = "";

		if (jc.contains("textures") && jc["textures"].is_object()) {
			auto& tex = jc["textures"];

			all = tex.value("all", "");

			p.frontTex = tex.value("front", all);
			p.backTex = tex.value("back", all);
			p.bottomTex = tex.value("bottom", all);
			p.leftTex = tex.value("left", all);
			p.rightTex = tex.value("right", all);

			p.isRepeat = tex.value("isRepeat", true);
		}

		pyramidsData.push_back(p);
	}

	for (auto& jc : j["frustumCube"])
	{
		FrustumCubeData c;

		// if the key not exist, then use default value to prevent error
		c.topLength = jc.value("topLength", 1.0f);
		c.topDepth = jc.value("topDepth", 1.0f);
		c.topOffsetX = jc.value("topOffsetX", 1.0f);
		c.topOffsetZ = jc.value("topOffsetZ", 1.0f);
		c.bottomLength = jc.value("bottomLength", 1.0f);
		c.bottomDepth = jc.value("bottomDepth", 1.0f);
		c.height = jc.value("height", 1.0f);

		c.r = jc.value("r", 1.0f);
		c.g = jc.value("g", 1.0f);
		c.b = jc.value("b", 1.0f);

		c.transX = jc.value("transX", 0.0f);
		c.transY = jc.value("transY", 0.0f);
		c.transZ = jc.value("transZ", 0.0f);

		c.rotX = jc.value("rotX", 0.0f);
		c.rotY = jc.value("rotY", 0.0f);
		c.rotZ = jc.value("rotZ", 0.0f);

		c.scaleX = jc.value("scaleX", 1.0f);
		c.scaleY = jc.value("scaleY", 1.0f);
		c.scaleZ = jc.value("scaleZ", 1.0f);

		c.isExpandable = jc.value("isExpandable", true);
		c.isSpecular = jc.value("isSpecular", true);
		c.shininess = jc.value("shininess", 50.0f);

		if (jc.contains("textures") && jc["textures"].is_object()) {
			auto& tex = jc["textures"];

			std::string all = tex.value("all", "");
			if (!all.empty()) {
				c.frontTex = c.backTex = c.topTex =
					c.bottomTex = c.leftTex = c.rightTex = all;
			}

			std::string top = tex.value("top", "");
			std::string bottom = tex.value("bottom", "");
			std::string front = tex.value("front", "");
			std::string back = tex.value("back", "");
			std::string left = tex.value("left", "");
			std::string right = tex.value("right", "");

			if (!top.empty())    c.topTex = top;
			if (!bottom.empty()) c.bottomTex = bottom;
			if (!front.empty())   c.frontTex = front;
			if (!back.empty())   c.backTex = back;
			if (!left.empty())   c.leftTex = left;
			if (!right.empty())   c.rightTex = right;

			c.isRepeat = tex.value("isRepeat", true);
		}

		frustumCubesData.push_back(c);
	}

	for (auto& jc : j["tetrahedrons"]) {
		TetrahedronData p;
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

		p.isSpecular = jc.value("isSpecular", true);
		p.shininess = jc.value("shininess", 50.0f);

		tetrahedronsData.push_back(p);
	}

	// When start program
	if (firstRun)
	{
		size_t i = 0;
		for (auto& data : cylindersData)
		{
			cylinders.push_back(std::make_unique<Cylinder>(data.baseRadius, data.topRadius, data.innerRadius, data.height, data.slices, data.stacks, data.style, data.isClose, data.lineWidth, data.r, data.g, data.b));
			cylinders[i]->Translate(data.transX, data.transY, data.transZ);
			cylinders[i]->Rotate(data.rotX, data.rotY, data.rotZ, false, 0.0f, 0.0f, 0.0f);
			cylinders[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			
			cylinders[i]->SetCylinderTexture(data.bodyTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.bodyTex, data.isRepeat));
			cylinders[i]->SetTopTexture(data.topTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.topTex, data.isRepeat));
			cylinders[i]->SetBottomTexture(data.bottomTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.bottomTex, data.isRepeat));
			cylinders[i]->SetIsSpecular(data.isSpecular);
			cylinders[i]->SetShininess(data.shininess);
			i++;
		}
		i = 0;
		for (auto& data : spheresData)
		{
			spheres.push_back(std::make_unique<Sphere>(data.radius, data.slices, data.stacks, data.style, data.lineWidth, data.r, data.g, data.b));
			
			spheres[i]->Translate(data.transX, data.transY, data.transZ);
			spheres[i]->Rotate(data.rotX, data.rotY, data.rotZ);
			spheres[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			spheres[i]->SetIsSpecular(data.isSpecular);

			spheres[i]->SetSphereTexture(data.sphereTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.sphereTex, data.isRepeat));
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
			cubes[i]->SetIsRepeat(data.isRepeat);
			cubes[i]->SetIsSpecular(data.isSpecular);
			cubes[i]->SetShininess(data.shininess);

			cubes[i]->SetFrontTexture(data.frontTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.frontTex, data.isRepeat));
			cubes[i]->SetBackTexture(data.backTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.backTex, data.isRepeat));
			cubes[i]->SetTopTexture(data.topTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.topTex, data.isRepeat));
			cubes[i]->SetBottomTexture(data.bottomTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.bottomTex, data.isRepeat));
			cubes[i]->SetLeftTexture(data.leftTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.leftTex, data.isRepeat));
			cubes[i]->SetRightTexture(data.rightTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.rightTex, data.isRepeat));
			i++;
		}
		i = 0;
		for (auto& data : pyramidsData)
		{
			pyramids.push_back(std::make_unique<Pyramid>(data.length, data.width, data.height, data.r, data.g, data.b));
			pyramids[i]->Translate(data.transX, data.transY, data.transZ);
			pyramids[i]->Rotate(data.rotX, data.rotY, data.rotZ);
			pyramids[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			
			pyramids[i]->SetFrontTexture(data.frontTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.frontTex, data.isRepeat));
			pyramids[i]->SetBackTexture(data.backTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.backTex, data.isRepeat));
			pyramids[i]->SetBottomTexture(data.bottomTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.bottomTex, data.isRepeat));
			pyramids[i]->SetLeftTexture(data.leftTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.leftTex, data.isRepeat));
			pyramids[i]->SetRightTexture(data.rightTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.rightTex, data.isRepeat));
			pyramids[i]->SetIsRepeat(data.isRepeat);
			pyramids[i]->SetIsSpecular(data.isSpecular);
			pyramids[i]->SetShininess(data.shininess);
			i++;
		}
		i = 0;
		for (auto& data : frustumCubesData)
		{
			frustumCubes.push_back(std::make_unique<FrustumCube>(data.topLength, data.topDepth, data.topOffsetX, data.topOffsetZ, data.bottomLength, data.bottomDepth, data.height, data.r, data.g, data.b));
			frustumCubes[i]->Translate(data.transX, data.transY, data.transZ);
			frustumCubes[i]->Rotate(data.rotX, data.rotY, data.rotZ);
			frustumCubes[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			frustumCubes[i]->SetExpandable(data.isExpandable);
			frustumCubes[i]->SetIsRepeat(data.isRepeat);
			frustumCubes[i]->SetIsSpecular(data.isSpecular);
			frustumCubes[i]->SetShininess(data.shininess);

			frustumCubes[i]->SetFrontTexture(data.frontTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.frontTex, data.isRepeat));
			frustumCubes[i]->SetBackTexture(data.backTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.backTex, data.isRepeat));
			frustumCubes[i]->SetTopTexture(data.topTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.topTex, data.isRepeat));
			frustumCubes[i]->SetBottomTexture(data.bottomTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.bottomTex, data.isRepeat));
			frustumCubes[i]->SetLeftTexture(data.leftTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.leftTex, data.isRepeat));
			frustumCubes[i]->SetRightTexture(data.rightTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(data.rightTex, data.isRepeat));
			i++;
		}
		i = 0;
		for (auto& data : tetrahedronsData)
		{
			tetrahedrons.push_back(std::make_unique<Tetrahedron>(data.length, data.width, data.height, data.r, data.g, data.b));
			tetrahedrons[i]->Translate(data.transX, data.transY, data.transZ);
			tetrahedrons[i]->Rotate(data.rotX, data.rotY, data.rotZ);
			tetrahedrons[i]->Scale(data.scaleX, data.scaleY, data.scaleZ);
			tetrahedrons[i]->SetIsRepeat(data.isRepeat);
			tetrahedrons[i]->SetIsSpecular(data.isSpecular);
			tetrahedrons[i]->SetShininess(data.shininess);
			i++;
		}
	}
	else
	{
		// Press Enter can refresh data, able to modify the 3D shape in runtime 
		for (size_t i = 0; i < cylinders.size() && i < cylindersData.size(); i++) {
			
			cylinders[i]->ClearTextures();
			cylinders[i]->SetCylinderTexture(cylindersData[i].bodyTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(cylindersData[i].bodyTex, cylindersData[i].isRepeat));
			cylinders[i]->SetTopTexture(cylindersData[i].topTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(cylindersData[i].topTex, cylindersData[i].isRepeat));
			cylinders[i]->SetBottomTexture(cylindersData[i].bottomTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(cylindersData[i].bottomTex, cylindersData[i].isRepeat));

			cylinders[i]->SetBaseRadius(cylindersData[i].baseRadius);
			cylinders[i]->SetTopRadius(cylindersData[i].topRadius);
			cylinders[i]->SetInnerRadius(cylindersData[i].innerRadius);
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
			cylinders[i]->SetIsSpecular(cylindersData[i].isSpecular);
			cylinders[i]->SetShininess(cylindersData[i].shininess);
		}

		for (size_t i = 0; i < spheres.size() && i < spheresData.size(); i++)
		{
			spheres[i]->ClearTextures();
			spheres[i]->SetSphereTexture(spheresData[i].sphereTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(spheresData[i].sphereTex, spheresData[i].isRepeat));

			spheres[i]->SetRadius(spheresData[i].radius);
			spheres[i]->SetSlices(spheresData[i].slices);
			spheres[i]->SetStacks(spheresData[i].stacks);
			spheres[i]->SetStyle(spheresData[i].style);
			spheres[i]->SetLineWidth(spheresData[i].lineWidth);
			spheres[i]->SetColor(spheresData[i].r, spheresData[i].g, spheresData[i].b);
			spheres[i]->Translate(spheresData[i].transX, spheresData[i].transY, spheresData[i].transZ);
			spheres[i]->Rotate(spheresData[i].rotX, spheresData[i].rotY, spheresData[i].rotZ);
			spheres[i]->Scale(spheresData[i].scaleX, spheresData[i].scaleY, spheresData[i].scaleZ);
			spheres[i]->SetIsSpecular(spheresData[i].isSpecular);
			spheres[i]->SetShininess(spheresData[i].shininess);
		}

		for (size_t i = 0; i < cubes.size() && i < cubesData.size(); i++)
		{
			cubes[i]->ClearTextures();
			cubes[i]->SetFrontTexture(cubesData[i].frontTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(cubesData[i].frontTex, cubesData[i].isRepeat));
			cubes[i]->SetBackTexture(cubesData[i].backTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(cubesData[i].backTex, cubesData[i].isRepeat));
			cubes[i]->SetTopTexture(cubesData[i].topTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(cubesData[i].topTex, cubesData[i].isRepeat));
			cubes[i]->SetBottomTexture(cubesData[i].bottomTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(cubesData[i].bottomTex, cubesData[i].isRepeat));
			cubes[i]->SetLeftTexture(cubesData[i].leftTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(cubesData[i].leftTex, cubesData[i].isRepeat));
			cubes[i]->SetRightTexture(cubesData[i].rightTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(cubesData[i].rightTex, cubesData[i].isRepeat));

			cubes[i]->SetLength(cubesData[i].length);
			cubes[i]->SetWidth(cubesData[i].width);
			cubes[i]->SetHeight(cubesData[i].height);
			cubes[i]->SetColor(cubesData[i].r, cubesData[i].g, cubesData[i].b);
			cubes[i]->Translate(cubesData[i].transX, cubesData[i].transY, cubesData[i].transZ);
			cubes[i]->Rotate(cubesData[i].rotX, cubesData[i].rotY, cubesData[i].rotZ);
			cubes[i]->Scale(cubesData[i].scaleX, cubesData[i].scaleY, cubesData[i].scaleZ);
			cubes[i]->SetExpandable(cubesData[i].isExpandable);
			cubes[i]->SetIsRepeat(cubesData[i].isRepeat);
			cubes[i]->SetIsSpecular(cubesData[i].isSpecular);
			cubes[i]->SetShininess(cubesData[i].shininess);
		}

		for (size_t i = 0; i < pyramids.size() && i < pyramidsData.size(); i++)
		{
			pyramids[i]->ClearTextures();
			pyramids[i]->SetFrontTexture(pyramidsData[i].frontTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(pyramidsData[i].frontTex, pyramidsData[i].isRepeat));
			pyramids[i]->SetBackTexture(pyramidsData[i].backTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(pyramidsData[i].backTex, pyramidsData[i].isRepeat));
			pyramids[i]->SetBottomTexture(pyramidsData[i].bottomTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(pyramidsData[i].bottomTex, pyramidsData[i].isRepeat));
			pyramids[i]->SetLeftTexture(pyramidsData[i].leftTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(pyramidsData[i].leftTex, pyramidsData[i].isRepeat));
			pyramids[i]->SetRightTexture(pyramidsData[i].rightTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(pyramidsData[i].rightTex, pyramidsData[i].isRepeat));

			pyramids[i]->SetLength(pyramidsData[i].length);
			pyramids[i]->SetWidth(pyramidsData[i].width);
			pyramids[i]->SetHeight(pyramidsData[i].height);
			pyramids[i]->SetColor(pyramidsData[i].r, pyramidsData[i].g, pyramidsData[i].b);
			pyramids[i]->Translate(pyramidsData[i].transX, pyramidsData[i].transY, pyramidsData[i].transZ);
			pyramids[i]->Rotate(pyramidsData[i].rotX, pyramidsData[i].rotY, pyramidsData[i].rotZ);
			pyramids[i]->Scale(pyramidsData[i].scaleX, pyramidsData[i].scaleY, pyramidsData[i].scaleZ);
			pyramids[i]->SetIsRepeat(pyramidsData[i].isRepeat);
			pyramids[i]->SetIsSpecular(pyramidsData[i].isSpecular);
			pyramids[i]->SetShininess(pyramidsData[i].shininess);
		}

		for (size_t i = 0; i < frustumCubes.size() && i < frustumCubesData.size(); i++)
		{
			frustumCubes[i]->ClearTextures();
			frustumCubes[i]->SetFrontTexture(frustumCubesData[i].frontTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(frustumCubesData[i].frontTex, frustumCubesData[i].isRepeat));
			frustumCubes[i]->SetBackTexture(frustumCubesData[i].backTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(frustumCubesData[i].backTex, frustumCubesData[i].isRepeat));
			frustumCubes[i]->SetTopTexture(frustumCubesData[i].topTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(frustumCubesData[i].topTex, frustumCubesData[i].isRepeat));
			frustumCubes[i]->SetBottomTexture(frustumCubesData[i].bottomTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(frustumCubesData[i].bottomTex, frustumCubesData[i].isRepeat));
			frustumCubes[i]->SetLeftTexture(frustumCubesData[i].leftTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(frustumCubesData[i].leftTex, frustumCubesData[i].isRepeat));
			frustumCubes[i]->SetRightTexture(frustumCubesData[i].rightTex.empty() ? LoadTexture("Assets/default.bmp", false) : LoadTexture(frustumCubesData[i].rightTex, frustumCubesData[i].isRepeat));

			frustumCubes[i]->SetTopLength(frustumCubesData[i].topLength);
			frustumCubes[i]->SetTopDepth(frustumCubesData[i].topDepth);
			frustumCubes[i]->SetTopOffsetX(frustumCubesData[i].topOffsetX);
			frustumCubes[i]->SetTopOffsetZ(frustumCubesData[i].topOffsetZ);
			frustumCubes[i]->SetBottomLength(frustumCubesData[i].bottomLength);
			frustumCubes[i]->SetBottomDepth(frustumCubesData[i].bottomDepth);
			frustumCubes[i]->SetHeight(frustumCubesData[i].height);
			frustumCubes[i]->SetColor(frustumCubesData[i].r, frustumCubesData[i].g, frustumCubesData[i].b);
			frustumCubes[i]->Translate(frustumCubesData[i].transX, frustumCubesData[i].transY, frustumCubesData[i].transZ);
			frustumCubes[i]->Rotate(frustumCubesData[i].rotX, frustumCubesData[i].rotY, frustumCubesData[i].rotZ);
			frustumCubes[i]->Scale(frustumCubesData[i].scaleX, frustumCubesData[i].scaleY, frustumCubesData[i].scaleZ);
			frustumCubes[i]->SetExpandable(frustumCubesData[i].isExpandable);
			frustumCubes[i]->SetIsRepeat(frustumCubesData[i].isRepeat);
			frustumCubes[i]->SetIsSpecular(frustumCubesData[i].isSpecular);
			frustumCubes[i]->SetShininess(frustumCubesData[i].shininess);

		}
		for (size_t i = 0; i < tetrahedrons.size() && i < tetrahedronsData.size(); i++)
		{
			tetrahedrons[i]->SetLength(tetrahedronsData[i].length);
			tetrahedrons[i]->SetWidth(tetrahedronsData[i].width);
			tetrahedrons[i]->SetHeight(tetrahedronsData[i].height);
			tetrahedrons[i]->SetColor(tetrahedronsData[i].r, tetrahedronsData[i].g, tetrahedronsData[i].b);
			tetrahedrons[i]->Translate(tetrahedronsData[i].transX, tetrahedronsData[i].transY, tetrahedronsData[i].transZ);
			tetrahedrons[i]->Rotate(tetrahedronsData[i].rotX, tetrahedronsData[i].rotY, tetrahedronsData[i].rotZ);
			tetrahedrons[i]->Scale(tetrahedronsData[i].scaleX, tetrahedronsData[i].scaleY, tetrahedronsData[i].scaleZ);
			tetrahedrons[i]->SetIsRepeat(tetrahedronsData[i].isRepeat);
			tetrahedrons[i]->SetIsSpecular(tetrahedronsData[i].isSpecular);
			tetrahedrons[i]->SetShininess(tetrahedronsData[i].shininess);
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

	for (auto& tetrahedron : tetrahedrons)
	{
		tetrahedron->Draw();
	}

	for (auto& frustumCube : frustumCubes)
	{
		frustumCube->Draw();
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

GLuint Object::LoadTexture(const std::string& filename, bool isRepeat)
{
	bool minimap = false;
	if (filename.empty()) {
		std::cout << "[LoadTexture] No texture filename provided." << std::endl;
		return 0; // 0 = no texture
	}

	HBITMAP hBMP = (HBITMAP)LoadImage(
		GetModuleHandle(NULL),
		filename.c_str(),
		IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE
	);

	if (!hBMP) {
		std::cout << "[LoadTexture] Failed to load bitmap: " << filename << std::endl;
		return 0;
	}

	BITMAP BMP;
	GetObject(hBMP, sizeof(BITMAP), &BMP);

	GLuint texID = 0;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	if (minimap) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	if (isRepeat) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	if (minimap) {
		float maxAniso = 0.0f;
		glGetFloatv(0x84FF, &maxAniso);
		glTexParameterf(GL_TEXTURE_2D, 0x84FE, maxAniso);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGB,
		BMP.bmWidth, BMP.bmHeight,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE,
		BMP.bmBits
	);

	if (minimap) {
		gluBuild2DMipmaps(
			GL_TEXTURE_2D, GL_RGB,
			BMP.bmWidth, BMP.bmHeight,
			GL_BGR_EXT, GL_UNSIGNED_BYTE,
			BMP.bmBits
		);
	}

	DeleteObject(hBMP);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "[LoadTexture] OpenGL error while loading texture: " << filename
			<< " Error code: " << err << std::endl;
		glDeleteTextures(1, &texID);
		return 0;
	}

	std::cout << "[LoadTexture] Successfully loaded texture: " << filename
		<< " ID: " << texID << std::endl;

	return texID;
}

