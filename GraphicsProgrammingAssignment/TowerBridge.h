#pragma once
#include "Object.h"
class TowerBridge
{
public:
	Object tower;
	Object bridge;
	TowerBridge() : tower("towerBridge.json"), bridge("bridge.json") {}
	void Draw(float rotation);
	void ReadData();
};

