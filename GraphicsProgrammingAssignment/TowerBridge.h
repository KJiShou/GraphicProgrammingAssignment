#pragma once
#include "Object.h"
class TowerBridge
{
public:
	Object* tower = new Object("towerBridge.json");
	Object* bridge = new Object("bridge.json");
	TowerBridge() {};
	void Draw(float rotation);
	void ReadData();
};

