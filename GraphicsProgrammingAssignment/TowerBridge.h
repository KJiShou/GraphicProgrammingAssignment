#pragma once
#include "Object.h"
class TowerBridge
{
public:
	Object object;
	TowerBridge() : object("towerBridge.json") {}
	void Draw();
	void ReadData();
};

