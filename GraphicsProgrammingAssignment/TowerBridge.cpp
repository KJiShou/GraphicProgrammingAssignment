#include "TowerBridge.h"

void TowerBridge::Draw(float rotation) {
	tower.Draw();
	bridge.Rotate(rotation, 0, 0, 0.0, 2.6, -2.0);
	bridge.Draw();
	glPushMatrix();
	glTranslatef(0, 0, 12);
	glRotatef(180, 0, 1, 0);
	tower.Draw();
	bridge.Rotate(rotation, 0, 0, 0.0, 2.6, -2.0);
	bridge.Draw();
	glPopMatrix();
}

void TowerBridge::ReadData() {
	tower.ReadData();
	bridge.ReadData();
}