#include "BackBone.h"

BackBone::~BackBone()
{
	delete root;
}

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
	leftUpperArm->Translate(-1.0, 1.8, 0);
	leftForearm->Translate(0.0, -0.95, 0);
	leftHand->Translate(0.0, -0.9, 0);

	rightUpperArm->Translate(1.0, 1.8, 0);
	rightForearm->Translate(0.0, -0.95, 0);
	rightHand->Translate(0.0, -0.9, 0);
	rightUpperArmOuter->Rotate(0, 180, 0);
	// index finger positions
	rightIndexBase->Translate(0.09f, -0.25f, 0.0f);
	rightIndexMid->Translate(0.0f, -0.13f, 0.0f);
	rightIndexTip->Translate(0.0f, -0.1f, 0.0f);
	// middle finger positions
	rightMiddleBase->Translate(0.03f, -0.25f, 0.0f);
	rightMiddleMid->Translate(0.0f, -0.13f, 0.0f);
	rightMiddleTip->Translate(0.0f, -0.1f, 0.0f);
	// ring finger positions
	rightRingBase->Translate(-0.03f, -0.25f, 0.0f);
	rightRingMid->Translate(0.0f, -0.13f, 0.0f);
	rightRingTip->Translate(0.0f, -0.1f, 0.0f);
	// little finger positions
	rightLittleBase->Translate(-0.09f, -0.25f, 0.0f);
	rightLittleMid->Translate(0.0f, -0.13f, 0.0f);
	rightLittleTip->Translate(0.0f, -0.1f, 0.0f);
	// thumb finger positions
	rightThumbSpread->Rotate(0.0f, 0.0f, -40.0f);
	rightThumbSpread->Translate(0.13f, -0.13f, 0.0f);
	rightThumbMid->Translate(0.0f, 0.0f, 0.0f);
	rightThumbTip->Translate(0.0f, -0.1f, 0.0f);

	// index finger positions
	leftIndexBase->Translate(0.09f, -0.25f, 0.0f);
	leftIndexMid->Translate(0.0f, -0.13f, 0.0f);
	leftIndexTip->Translate(0.0f, -0.1f, 0.0f);
	// middle finger positions
	leftMiddleBase->Translate(0.03f, -0.25f, 0.0f);
	leftMiddleMid->Translate(0.0f, -0.13f, 0.0f);
	leftMiddleTip->Translate(0.0f, -0.1f, 0.0f);
	// ring finger positions
	leftRingBase->Translate(-0.03f, -0.25f, 0.0f);
	leftRingMid->Translate(0.0f, -0.13f, 0.0f);
	leftRingTip->Translate(0.0f, -0.1f, 0.0f);
	// little finger positions
	leftLittleBase->Translate(-0.09f, -0.25f, 0.0f);
	leftLittleMid->Translate(0.0f, -0.13f, 0.0f);
	leftLittleTip->Translate(0.0f, -0.1f, 0.0f);
	// thumb finger positions
	leftThumbSpread->Rotate(0.0f, 0.0f, 40.0f);
	leftThumbSpread->Translate(-0.13f, -0.13f, 0.0f);
	leftThumbMid->Translate(0.0f, 0.0f, 0.0f);
	leftThumbTip->Translate(0.0f, -0.1f, 0.0f);


	// leg
	leftUpperLeg->Translate(-0.3, -0.5, 0);
	leftLowerLeg->Translate(0, -0.95, 0);
	leftFoot->Translate(0, -0.9, 0);

	rightUpperLeg->Translate(0.3, -0.5, 0);
	rightLowerLeg->Translate(0, -0.95, 0);
	rightFoot->Translate(0, -0.9, 0);
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
	leftUpperArm->AddChild(leftUpperArmOuter);
	leftForearm->AddChild(leftHand);
	leftForearm->AddChild(leftForearmOuter);
	// hand -> index finger
	leftHand->AddChild(leftIndexBase);
	leftIndexBase->AddChild(leftIndexMid);
	leftIndexMid->AddChild(leftIndexTip);
	// hand -> middle finger
	leftHand->AddChild(leftMiddleBase);
	leftMiddleBase->AddChild(leftMiddleMid);
	leftMiddleMid->AddChild(leftMiddleTip);
	// hand -> ring finger
	leftHand->AddChild(leftRingBase);
	leftRingBase->AddChild(leftRingMid);
	leftRingMid->AddChild(leftRingTip);
	// hand -> little finger
	leftHand->AddChild(leftLittleBase);
	leftLittleBase->AddChild(leftLittleMid);
	leftLittleMid->AddChild(leftLittleTip);
	// hand -> thumb finger
	leftHand->AddChild(leftThumbSpread);
	leftThumbSpread->AddChild(leftThumbMid);
	leftThumbMid->AddChild(leftThumbTip);

	// right arm
	body->AddChild(rightUpperArm);
	rightUpperArm->AddChild(rightForearm);
	rightUpperArm->AddChild(rightUpperArmOuter);
	rightForearm->AddChild(rightHand);
	rightForearm->AddChild(rightForearmOuter);
	// hand -> index finger
	rightHand->AddChild(rightIndexBase);
	rightIndexBase->AddChild(rightIndexMid);
	rightIndexMid->AddChild(rightIndexTip);
	// hand -> middle finger
	rightHand->AddChild(rightMiddleBase);
	rightMiddleBase->AddChild(rightMiddleMid);
	rightMiddleMid->AddChild(rightMiddleTip);
	// hand -> ring finger
	rightHand->AddChild(rightRingBase);
	rightRingBase->AddChild(rightRingMid);
	rightRingMid->AddChild(rightRingTip);
	// hand -> little finger
	rightHand->AddChild(rightLittleBase);
	rightLittleBase->AddChild(rightLittleMid);
	rightLittleMid->AddChild(rightLittleTip);
	// hand -> thumb finger
	rightHand->AddChild(rightThumbSpread);
	rightThumbSpread->AddChild(rightThumbMid);
	rightThumbMid->AddChild(rightThumbTip);

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
	leftIndexBase->ReadData();
	leftIndexMid->ReadData();
	leftIndexTip->ReadData();
	leftMiddleBase->ReadData();
	leftMiddleMid->ReadData();
	leftMiddleTip->ReadData();
	leftRingBase->ReadData();
	leftRingMid->ReadData();
	leftRingTip->ReadData();
	leftLittleBase->ReadData();
	leftLittleMid->ReadData();
	leftLittleTip->ReadData();
	leftThumbMid->ReadData();
	leftThumbTip->ReadData();
	rightIndexBase->ReadData();
	rightIndexMid->ReadData();
	rightIndexTip->ReadData();
	rightMiddleBase->ReadData();
	rightMiddleMid->ReadData();
	rightMiddleTip->ReadData();
	rightRingBase->ReadData();
	rightRingMid->ReadData();
	rightRingTip->ReadData();
	rightLittleBase->ReadData();
	rightLittleMid->ReadData();
	rightLittleTip->ReadData();
	rightThumbMid->ReadData();
	rightThumbTip->ReadData();
	headBone->ReadData();
	leftUpperLeg->ReadData();
	leftLowerLeg->ReadData();
	leftFoot->ReadData();
	rightUpperLeg->ReadData();
	rightLowerLeg->ReadData();
	rightFoot->ReadData();
	pelvis->ReadData();
	leftUpperArmOuter->ReadData();
	rightUpperArmOuter->ReadData();
	leftForearmOuter->ReadData();
	rightForearmOuter->ReadData();
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
	rightForearmRotation[0] = -clamp(x, 0.0f, 140.0f);
	rightForearmRotation[1] = clamp(y, -90.0f, 90.0f);
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

void BackBone::RotateRightHandFinger(float base, float mid, float tip)
{
	rightIndexBaseRot = clamp(base, 0.0f, 90.0f);
	rightIndexMidRot = clamp(mid, 0.0f, 90.0f);
	rightIndexTipRot = clamp(tip, 0.0f, 60.0f);
	rightMiddleBaseRot = clamp(base, 0.0f, 90.0f);
	rightMiddleMidRot = clamp(mid, 0.0f, 90.0f);
	rightMiddleTipRot = clamp(tip, 0.0f, 60.0f);
	rightRingBaseRot = clamp(base, 0.0f, 90.0f);
	rightRingMidRot = clamp(mid, 0.0f, 90.0f);
	rightRingTipRot = clamp(tip, 0.0f, 60.0f);
	rightLittleBaseRot = clamp(base, 0.0f, 90.0f);
	rightLittleMidRot = clamp(mid, 0.0f, 90.0f);
	rightLittleTipRot = clamp(tip, 0.0f, 60.0f);
	rightThumbSpreadRot = clamp(base, 0.0f, 45.0f);
	rightThumbMidRot = clamp(mid, 0.0f, 90.0f);
	rightThumbTipRot = clamp(tip, 0.0f, 60.0f);
}

void BackBone::RotateRightIndex(float base, float mid, float tip)
{
	rightIndexBaseRot = clamp(base, 0.0f, 90.0f);
	rightIndexMidRot = clamp(mid, 0.0f, 90.0f);
	rightIndexTipRot = clamp(tip, 0.0f, 60.0f);
}

void BackBone::RotateRightMiddle(float base, float mid, float tip)
{
	rightMiddleBaseRot = clamp(base, 0.0f, 90.0f);
	rightMiddleMidRot = clamp(mid, 0.0f, 90.0f);
	rightMiddleTipRot = clamp(tip, 0.0f, 60.0f);
}

void BackBone::RotateRightRing(float base, float mid, float tip)
{
	rightRingBaseRot = clamp(base, 0.0f, 90.0f);
	rightRingMidRot = clamp(mid, 0.0f, 90.0f);
	rightRingTipRot = clamp(tip, 0.0f, 60.0f);
}

void BackBone::RotateRightLittle(float base, float mid, float tip)
{
	rightLittleBaseRot = clamp(base, 0.0f, 90.0f);
	rightLittleMidRot = clamp(mid, 0.0f, 90.0f);
	rightLittleTipRot = clamp(tip, 0.0f, 60.0f);
}

void BackBone::RotateRightThumb(float base, float mid, float tip)
{
	rightThumbSpreadRot = clamp(base, 0.0f, 45.0f);
	rightThumbMidRot = clamp(mid, 0.0f, 90.0f);
	rightThumbTipRot = clamp(tip, 0.0f, 60.0f);
}

void BackBone::RotateLeftHandFinger(float base, float mid, float tip)
{
	leftIndexBaseRot = clamp(base, 0.0f, 90.0f);
	leftIndexMidRot = clamp(mid, 0.0f, 90.0f);
	leftIndexTipRot = clamp(tip, 0.0f, 60.0f);
	leftMiddleBaseRot = clamp(base, 0.0f, 90.0f);
	leftMiddleMidRot = clamp(mid, 0.0f, 90.0f);
	leftMiddleTipRot = clamp(tip, 0.0f, 60.0f);
	leftRingBaseRot = clamp(base, 0.0f, 90.0f);
	leftRingMidRot = clamp(mid, 0.0f, 90.0f);
	leftRingTipRot = clamp(tip, 0.0f, 60.0f);
	leftLittleBaseRot = clamp(base, 0.0f, 90.0f);
	leftLittleMidRot = clamp(mid, 0.0f, 90.0f);
	leftLittleTipRot = clamp(tip, 0.0f, 60.0f);
	leftThumbSpreadRot = clamp(base, 0.0f, 45.0f);
	leftThumbMidRot = clamp(mid, 0.0f, 90.0f);
	leftThumbTipRot = clamp(tip, 0.0f, 60.0f);
}

void BackBone::RotateLeftIndex(float base, float mid, float tip)
{
	leftIndexBaseRot = clamp(base, 0.0f, 90.0f);
	leftIndexMidRot = clamp(mid, 0.0f, 90.0f);
	leftIndexTipRot = clamp(tip, 0.0f, 60.0f);
}

void BackBone::RotateLeftMiddle(float base, float mid, float tip)
{
	leftMiddleBaseRot = clamp(base, 0.0f, 90.0f);
	leftMiddleMidRot = clamp(mid, 0.0f, 90.0f);
	leftMiddleTipRot = clamp(tip, 0.0f, 60.0f);
}

void BackBone::RotateLeftRing(float base, float mid, float tip)
{
	leftRingBaseRot = clamp(base, 0.0f, 90.0f);
	leftRingMidRot = clamp(mid, 0.0f, 90.0f);
	leftRingTipRot = clamp(tip, 0.0f, 60.0f);
}

void BackBone::RotateLeftLittle(float base, float mid, float tip)
{
	leftLittleBaseRot = clamp(base, 0.0f, 90.0f);
	leftLittleMidRot = clamp(mid, 0.0f, 90.0f);
	leftLittleTipRot = clamp(tip, 0.0f, 60.0f);
}

void BackBone::RotateLeftThumb(float base, float mid, float tip)
{
	leftThumbSpreadRot = clamp(base, 0.0f, 45.0f);
	leftThumbMidRot = clamp(mid, 0.0f, 90.0f);
	leftThumbTipRot = clamp(tip, 0.0f, 60.0f);
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
	rightIndexBase->Rotate(-rightIndexBaseRot, 0, 0);
	rightIndexMid->Rotate(-rightIndexMidRot, 0, 0);
	rightIndexTip->Rotate(-rightIndexTipRot, 0, 0);
	rightMiddleBase->Rotate(-rightMiddleBaseRot, 0, 0);
	rightMiddleMid->Rotate(-rightMiddleMidRot, 0, 0);
	rightMiddleTip->Rotate(-rightMiddleTipRot, 0, 0);
	rightRingBase->Rotate(-rightMiddleBaseRot, 0, 0);
	rightRingMid->Rotate(-rightMiddleMidRot, 0, 0);
	rightRingTip->Rotate(-rightMiddleTipRot, 0, 0);
	rightLittleBase->Rotate(-rightMiddleBaseRot, 0, 0);
	rightLittleMid->Rotate(-rightMiddleMidRot, 0, 0);
	rightLittleTip->Rotate(-rightMiddleTipRot, 0, 0);
	rightThumbSpread->Rotate(0.0f, 0.0f, rightThumbSpreadRot);
	rightThumbMid->Rotate(-rightThumbMidRot, 0, 0);
	rightThumbTip->Rotate(-rightThumbTipRot, 0, 0);

	leftIndexBase->Rotate(-leftIndexBaseRot, 0, 0);
	leftIndexMid->Rotate(-leftIndexMidRot, 0, 0);
	leftIndexTip->Rotate(-leftIndexTipRot, 0, 0);
	leftMiddleBase->Rotate(-leftMiddleBaseRot, 0, 0);
	leftMiddleMid->Rotate(-leftMiddleMidRot, 0, 0);
	leftMiddleTip->Rotate(-leftMiddleTipRot, 0, 0);
	leftRingBase->Rotate(-leftMiddleBaseRot, 0, 0);
	leftRingMid->Rotate(-leftMiddleMidRot, 0, 0);
	leftRingTip->Rotate(-leftMiddleTipRot, 0, 0);
	leftLittleBase->Rotate(-leftMiddleBaseRot, 0, 0);
	leftLittleMid->Rotate(-leftMiddleMidRot, 0, 0);
	leftLittleTip->Rotate(-leftMiddleTipRot, 0, 0);
	leftThumbSpread->Rotate(0.0f, 0.0f, -leftThumbSpreadRot);
	leftThumbMid->Rotate(-leftThumbMidRot, 0, 0);
	leftThumbTip->Rotate(-leftThumbTipRot, 0, 0);

	leftUpperLeg->Rotate(leftUpperLegRotation[0], leftUpperLegRotation[1], leftUpperLegRotation[2]);
	leftLowerLeg->Rotate(leftLowerLegRotation[0], leftLowerLegRotation[1], leftLowerLegRotation[2]);
	leftFoot->Rotate(leftFootRotation[0], leftFootRotation[1], leftFootRotation[2]);
	rightUpperLeg->Rotate(rightUpperLegRotation[0], rightUpperLegRotation[1], rightUpperLegRotation[2]);
	rightLowerLeg->Rotate(rightLowerLegRotation[0], rightLowerLegRotation[1], rightLowerLegRotation[2]);
	rightFoot->Rotate(rightFootRotation[0], rightFootRotation[1], rightFootRotation[2]);

	root->Draw();
}