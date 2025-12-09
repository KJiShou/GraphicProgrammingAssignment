#include "BackBone.h"

void BackBone::SetBone() {
	//====================
	// position adjustment
	//====================
	// head
	headBone->Translate(0, 1.7, 0);
	pelvis->Translate(0, 0.9, 0);
	
	// body
	body->Translate(0, 1, 0);
	
	// arm
	leftUpperArm->Translate(-0.6, 1.8, 0);
	leftForearm->Translate(0.0, -0.95, 0);
	leftHand->Translate(0.0, -1.75, 0);

	rightUpperArm->Translate(0.6, 1.8, 0);
	rightForearm->Translate(0.0, -0.95, 0);
	rightHand->Translate(0.0, -1.75, 0);

	// leg
	leftUpperLeg->Translate(-0.3, -0.5, 0);
	leftLowerLeg->Translate(0, -0.95, 0);
	leftFoot->Translate(0, -1.75, 0);

	rightUpperLeg->Translate(0.3, -0.5, 0);
	rightLowerLeg->Translate(0, -0.95, 0);
	rightFoot->Translate(0, -1.75, 0);
	// ====================
	// child relationship
	// ====================
	
	// root -> body
	root->AddChild(body);
	root->AddChild(pelvis);

	// body -> head
	body->AddChild(headBone);

	// left arm
	body->AddChild(leftUpperArm);
	leftUpperArm->AddChild(leftForearm);
	leftForearm->AddChild(leftHand);

	// right arm
	body->AddChild(rightUpperArm);
	rightUpperArm->AddChild(rightForearm);
	rightForearm->AddChild(rightHand);

	// left leg
	pelvis->AddChild(leftUpperLeg);
	leftUpperLeg->AddChild(leftLowerLeg);
	leftLowerLeg->AddChild(leftFoot);

	// right leg
	pelvis->AddChild(rightUpperLeg);
	rightUpperLeg->AddChild(rightLowerLeg);
	rightLowerLeg->AddChild(rightFoot);
}

void BackBone::ReadData() {
	root->ReadData();
	body->ReadData();
	leftUpperArm->ReadData();
	leftForearm->ReadData();
	leftHand->ReadData();
	rightUpperArm->ReadData();
	rightForearm->ReadData();
	rightHand->ReadData();
	headBone->ReadData();
	leftUpperLeg->ReadData();
	leftLowerLeg->ReadData();
	leftFoot->ReadData();
	rightUpperLeg->ReadData();
	rightLowerLeg->ReadData();
	rightFoot->ReadData();
	pelvis->ReadData();
}

float clamp(float v, float min, float max) {
	if (v < min) return min;
	if (v > max) return max;
	return v;
}


void BackBone::RotateHead(float x, float y, float z)
{
	headRotation[0] = clamp(x, -40.0f, 40.0f);
	headRotation[1] = clamp(y, -70.0f, 70.0f);
	headRotation[2] = clamp(z, -30.0f, 30.0f);
}

void BackBone::RotateBody(float x, float y, float z)
{
	bodyRotation[0] = clamp(x, -30.0f, 30.0f);
	bodyRotation[1] = clamp(y, -45.0f, 45.0f);
	bodyRotation[2] = clamp(z, -20.0f, 20.0f);
}

void BackBone::RotatePelvis(float x, float y, float z)
{
	pelvisRotation[0] = -clamp(x, -20.0f, 20.0f);
	pelvisRotation[1] = clamp(y, -20.0f, 20.0f);
	pelvisRotation[2] = clamp(z, -15.0f, 15.0f);
}

void BackBone::RotateLeftUpperArm(float x, float y, float z)
{
	float rx = clamp(x, -60.0f, 90.0f);
	float ry = clamp(y, -45.0f, 45.0f);
	float rz = clamp(z, -30.0f, 30.0f);

	leftUpperArmRotation[0] = -rx;
	leftUpperArmRotation[1] = -ry;
	leftUpperArmRotation[2] = -rz;
}

void BackBone::RotateLeftForearm(float x, float y)
{
	leftForearmRotation[0] = -clamp(x, 0.0f, 140.0f); 
	leftForearmRotation[1] = -clamp(y, -90.0f, 90.0f); 
}

void BackBone::RotateLeftHand(float x, float y, float z)
{
	leftHandRotation[0] = clamp(x, -45.0f, 45.0f);
	leftHandRotation[1] = clamp(y, -30.0f, 30.0f);
	leftHandRotation[2] = clamp(z, -45.0f, 45.0f);
}

void BackBone::RotateRightUpperArm(float x, float y, float z)
{
	float rx = clamp(x, -135.0f, 45.0f);
	float rz = clamp(z, -20.0f, 100.0f);
	float ry = clamp(y, -90.0f, 90.0f);

	rightUpperArmRotation[0] = -rx;
	rightUpperArmRotation[1] = -ry;
	rightUpperArmRotation[2] = rz;
}

void BackBone::RotateRightForearm(float x, float y)
{
	leftForearmRotation[0] = -clamp(x, 0.0f, 140.0f);
	leftForearmRotation[1] = clamp(y, -90.0f, 90.0f);
}

void BackBone::RotateRightHand(float x, float y, float z)
{
	rightHandRotation[0] = clamp(x, -45.0f, 45.0f);
	rightHandRotation[1] = clamp(y, -30.0f, 30.0f);
	rightHandRotation[2] = clamp(z, -45.0f, 45.0f);
}

void BackBone::RotateLeftUpperLeg(float x, float y, float z)
{
	float rx = clamp(x, -45.0f, 90.0f);
	float rz = clamp(z, -15.0f, 60.0f); 
	float ry = clamp(y, -45.0f, 45.0f);
	leftUpperLegRotation[0] = -rx; 
	leftUpperLegRotation[1] = -ry; 
	leftUpperLegRotation[2] = -rz; 
}

void BackBone::RotateLeftLowerLeg(float x)
{
	leftLowerLegRotation[0] = -clamp(x, -130.0f, 0.0f);
}

void BackBone::RotateLeftFoot(float x, float y, float z)
{
	leftFootRotation[0] = clamp(x, -30.0f, 45.0f);
	leftFootRotation[1] = clamp(y, -30.0f, 30.0f);
	leftFootRotation[2] = clamp(z, -15.0f, 15.0f);
}

void BackBone::RotateRightUpperLeg(float x, float y, float z)
{
	float rx = clamp(x, -90.0f, 45.0f);
	float rz = clamp(z, -15.0f, 60.0f);
	float ry = clamp(y, -45.0f, 45.0f);

	rightUpperLegRotation[0] = -rx;
	rightUpperLegRotation[1] = ry;
	rightUpperLegRotation[2] = rz;
}

void BackBone::RotateRightLowerLeg(float x) {
	rightLowerLegRotation[0] = -clamp(x, -130.0f, 0.0f);
}

void BackBone::RotateRightFoot(float x, float y, float z)
{
	rightFootRotation[0] = clamp(x, -30.0f, 45.0f);
	rightFootRotation[1] = clamp(y, -30.0f, 30.0f);
	rightFootRotation[2] = clamp(z, -15.0f, 15.0f);
}


void BackBone::Move(float x, float y, float z) {
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void BackBone::Rotate(float x, float y, float z)
{
	rotation[0] = x;
	rotation[1] = y;
	rotation[2] = z;
}

void BackBone::Draw() {
	root->Translate(position[0], position[1], position[2]);
	root->Rotate(rotation[0], rotation[1], rotation[2], 0.0f, 0.45f, 0.0f);
	headBone->Rotate(headRotation[0], headRotation[1], headRotation[2], 0.0f, 0.5f, 0.0f);
	body->Rotate(bodyRotation[0], bodyRotation[1], bodyRotation[2]);
	pelvis->Rotate(pelvisRotation[0], pelvisRotation[1], pelvisRotation[2]);
	leftUpperArm->Rotate(leftUpperArmRotation[0], leftUpperArmRotation[1], leftUpperArmRotation[2]);
	leftForearm->Rotate(leftForearmRotation[0], leftForearmRotation[1], leftForearmRotation[2]);
	leftHand->Rotate(leftHandRotation[0], leftHandRotation[1], leftHandRotation[2]);
	rightUpperArm->Rotate(rightUpperArmRotation[0], rightUpperArmRotation[1], rightUpperArmRotation[2]);
	rightForearm->Rotate(rightForearmRotation[0], rightForearmRotation[1], rightForearmRotation[2]);
	rightHand->Rotate(rightHandRotation[0], rightHandRotation[1], rightHandRotation[2]);
	leftUpperLeg->Rotate(leftUpperLegRotation[0], leftUpperLegRotation[1], leftUpperLegRotation[2]);
	leftLowerLeg->Rotate(leftLowerLegRotation[0], leftLowerLegRotation[1], leftLowerLegRotation[2]);
	leftFoot->Rotate(leftFootRotation[0], leftFootRotation[1], leftFootRotation[2]);
	rightUpperLeg->Rotate(rightUpperLegRotation[0], rightUpperLegRotation[1], rightUpperLegRotation[2]);
	rightLowerLeg->Rotate(rightLowerLegRotation[0], rightLowerLegRotation[1], rightLowerLegRotation[2]);
	rightFoot->Rotate(rightFootRotation[0], rightFootRotation[1], rightFootRotation[2]);

	root->Draw();
}