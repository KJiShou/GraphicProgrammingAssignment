#include "TowerBridge.h"

void TowerBridge::Draw() {
	tower.Draw();
	//bridge.Draw();
}

void TowerBridge::ReadData() {
	tower.ReadData();
	bridge.ReadData();
}