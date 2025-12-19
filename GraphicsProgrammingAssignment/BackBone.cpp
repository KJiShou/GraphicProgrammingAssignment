#include "BackBone.h"

BackBone::~BackBone()
{
	delete root;
	delete headBone;
	delete body;
	delete wing;
	delete pelvis;

	delete leftUpperArm;
	delete leftUpperArmOuter;
	delete leftForearm;
	delete leftForearmOuter;
	delete leftHand;

	delete rightUpperArm;
	delete rightUpperArmOuter;
	delete rightForearm;
	delete rightForearmOuter;
	delete rightHand;

	delete rightIndexBase;
	delete rightIndexMid;
	delete rightIndexTip;
	delete rightMiddleBase;
	delete rightMiddleMid;
	delete rightMiddleTip;
	delete rightRingBase;
	delete rightRingMid;
	delete rightRingTip;
	delete rightLittleBase;
	delete rightLittleMid;
	delete rightLittleTip;
	delete rightThumbSpread;
	delete rightThumbMid;
	delete rightThumbTip;

	delete leftIndexBase;
	delete leftIndexMid;
	delete leftIndexTip;
	delete leftMiddleBase;
	delete leftMiddleMid;
	delete leftMiddleTip;
	delete leftRingBase;
	delete leftRingMid;
	delete leftRingTip;
	delete leftLittleBase;
	delete leftLittleMid;
	delete leftLittleTip;
	delete leftThumbSpread;
	delete leftThumbMid;
	delete leftThumbTip;

	delete leftUpperLeg;
	delete leftLowerLeg;
	delete leftFoot;
	delete rightUpperLeg;
	delete rightLowerLeg;
	delete rightFoot;
	delete leftLegFrontArmor;
	delete leftLegBackArmor;
	delete leftLegSideArmor;
	delete rightLegFrontArmor;
	delete rightLegBackArmor;
	delete rightLegSideArmor;
}


void BackBone::SetBone() {
	//====================
	// position adjustment
	//====================
	// head
	headBone->Translate(0, 1.7, 0);
	pelvis->Translate(0, 1.3, 0);
	
	// body
	body->Translate(0, 1, 0);
	
	// arm
	leftUpperArmJoint->Translate(-1.0, 1.8, 0);
	leftForearm->Translate(0.0, -0.95, 0);
	leftHand->Translate(0.0, -0.9, 0);

	rightUpperArmJoint->Translate(1.0, 1.8, 0);
	rightUpperArmJointOuter->Rotate(0, 180, 0);
	rightUpperArmOuter->Rotate(0, 180, 0);
	rightForearm->Translate(0.0, -0.95, 0);
	rightHand->Translate(0.0, -0.9, 0);
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
	leftLegFrontArmor->Translate(-0.3, -0.5, 0.1);
	leftLegFrontArmor->Scale(1.2, 1.7, 1.2);
	leftLegBackArmor->Translate(-0.3, -0.5, -0.1);
	leftLegBackArmor->Scale(1.2, 1.7, 1.2);
	leftLegSideArmor->Translate(-0.3, -0.5, 0.0);
	leftLegSideArmor->Scale(1.2, 1.7, 1.7);
	leftUpperLeg->Translate(-0.3, -0.3, 0.0);
	leftUpperLeg->Scale(1.2, 1.2, 1.2);
	leftUpperLeg->Translate(-0.4, -0.3, 0.0);
	leftLowerLeg->Translate(0, -0.95, 0);
	leftFoot->Translate(0, -1.4, 0);

	rightLegFrontArmor->Translate(0.3, -0.5, 0.1);
	rightLegFrontArmor->Scale(1.2, 1.7, 1.2);
	rightLegBackArmor->Translate(0.3, -0.5, -0.1);
	rightLegBackArmor->Scale(1.2, 1.7, 1.2);
	rightLegSideArmor->Translate(0.3, -0.5, 0.0);
	rightLegSideArmor->Scale(1.2, 1.7, 1.7);
	rightUpperLeg->Translate(0.3, -0.3, 0);
	rightUpperLeg->Scale(1.2, 1.2, 1.2);
	rightUpperLeg->Translate(0.4, -0.3, 0);
	rightLowerLeg->Translate(0, -0.95, 0);
	rightFoot->Translate(0, -1.4, 0);
	// ====================
	// child relationship
	// ====================
	
	// root -> body
	root->AddChild(body);
	root->AddChild(pelvis);

	// body -> head
	body->AddChild(headBone);
	body->AddChild(wing);

	// left arm
	body->AddChild(leftUpperArmJoint);
	leftUpperArmJoint->AddChild(leftUpperArm);
	leftUpperArmJoint->AddChild(leftUpperArmJointOuter);
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
	body->AddChild(rightUpperArmJoint);
	rightUpperArmJoint->AddChild(rightUpperArm);
	rightUpperArmJoint->AddChild(rightUpperArmJointOuter);
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
	pelvis->AddChild(leftLegFrontArmor);
	pelvis->AddChild(leftLegBackArmor);
	pelvis->AddChild(leftLegSideArmor);
	leftUpperLeg->AddChild(leftLowerLeg);
	leftLowerLeg->AddChild(leftFoot);

	// right leg
	pelvis->AddChild(rightUpperLeg);
	pelvis->AddChild(rightLegFrontArmor);
	pelvis->AddChild(rightLegBackArmor);
	pelvis->AddChild(rightLegSideArmor);
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
	leftLegFrontArmor->ReadData();
	leftLegBackArmor->ReadData();
	leftLegSideArmor->ReadData();
	leftLowerLeg->ReadData();
	leftFoot->ReadData();
	rightUpperLeg->ReadData();
	rightLegFrontArmor->ReadData();
	rightLegBackArmor->ReadData();
	rightLegSideArmor->ReadData();
	rightLowerLeg->ReadData();
	rightFoot->ReadData();
	pelvis->ReadData();
	leftUpperArmOuter->ReadData();
	rightUpperArmOuter->ReadData();
	leftForearmOuter->ReadData();
	rightForearmOuter->ReadData();
	rightUpperArmJoint->ReadData();
	rightUpperArmJointOuter->ReadData();
	leftUpperArmJoint->ReadData();
	leftUpperArmJointOuter->ReadData();
	wing->ReadData();
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
	float rx = clamp(x, -45.0f, 180.0f);
	float rz = clamp(z, -20.0f, 100);
	float ry = clamp(y, -90.0f, 90.0f);

	leftUpperArmJointArmorRotation[0] = -rx;
	if (rz > 70) leftUpperArmJointArmorRotation[2] = -(rz - 70);

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
	float rx = clamp(x, -45.0f, 180.0f);
	float rz = clamp(z, -20.0f, 100);
	float ry = clamp(y, -90.0f, 90.0f);

	rightUpperArmJointArmorRotation[0] = -rx;
	if (rz > 70) rightUpperArmJointArmorRotation[2] = -(rz-70);

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
	float rx = clamp(x, -120.0f, 90.0f);
	float rz = clamp(z, -15.0f, 60.0f); 
	float ry = clamp(y, -45.0f, 45.0f);

	if (rx > 20) leftLegFrontArmorRotation[0] = -(rx - 20) * 0.9f;
	if (rx < 0) leftLegBackArmorRotation[0] = -rx;
	if (rz > 10) leftLegSideArmorRotation[2] = -(rz - 10) / 2.0f;

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
	float rx = clamp(x, -120.0f, 90.0f);
	float rz = clamp(z, -15.0f, 60.0f);
	float ry = clamp(y, -45.0f, 45.0f);

	if (rx > 20) rightLegFrontArmorRotation[0] = -(rx - 20) * 0.9f;
	if (rx < 0) rightLegBackArmorRotation[0] = -rx;
	if (rz > 10) rightLegSideArmorRotation[2] = (rz-10) / 2.0f;

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
	//===========================
	// Root Movement and Rotation
	//===========================
	root->Translate(position[0], position[1], position[2]);
	root->Rotate(rotation[0], rotation[1], rotation[2], 0.0f, 0.45f, 0.0f);

	//===========================
	// Head Rotation
	//===========================
	headBone->Rotate(headRotation[0], headRotation[1], headRotation[2], 0.0f, 0.5f, 0.0f);

	//===========================
	// Body Rotation
	//===========================
	body->Rotate(bodyRotation[0], bodyRotation[1], bodyRotation[2], 0.0f, 0.3f, 0.0f);

	//===========================
	// Pelvis Rotation
	//===========================
	pelvis->Rotate(pelvisRotation[0], pelvisRotation[1], pelvisRotation[2]);

	//===========================
	// Left Arm Rotation
	//===========================
	leftUpperArmJointOuter->Rotate(leftUpperArmJointArmorRotation[0], leftUpperArmJointArmorRotation[1], leftUpperArmJointArmorRotation[2]);
	leftUpperArm->Rotate(leftUpperArmRotation[0], leftUpperArmRotation[1], leftUpperArmRotation[2]);
	leftForearm->Rotate(leftForearmRotation[0], 90 + leftForearmRotation[1], leftForearmRotation[2]);
	leftHand->Rotate(leftHandRotation[0], leftHandRotation[1], leftHandRotation[2]);

	//===========================
	// Right Arm Rotation
	//===========================
	rightUpperArmJointOuter->Rotate(rightUpperArmJointArmorRotation[0], rightUpperArmJointArmorRotation[1] + 180.0f, rightUpperArmJointArmorRotation[2]);
	rightUpperArm->Rotate(rightUpperArmRotation[0], rightUpperArmRotation[1], rightUpperArmRotation[2]);
	rightForearm->Rotate(rightForearmRotation[0], -90 + rightForearmRotation[1], rightForearmRotation[2]);
	rightHand->Rotate(rightHandRotation[0], rightHandRotation[1], rightHandRotation[2]);

	//===========================
	// Right Hand Finger
	//===========================
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

	//===========================
	// Left Hand Finger
	//===========================
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

	//===========================
	// Left Leg
	//===========================
	leftLegFrontArmor->Rotate(leftLegFrontArmorRotation[0], leftLegFrontArmorRotation[1], leftLegFrontArmorRotation[2], 0.0f, 0.7f, 0.15f);
	leftLegBackArmor->Rotate(leftLegBackArmorRotation[0], leftLegBackArmorRotation[1], leftLegBackArmorRotation[2], 0.0f, 0.7f, -0.15f);
	leftLegSideArmor->Rotate(leftLegSideArmorRotation[0], leftLegSideArmorRotation[1], leftLegSideArmorRotation[2], -0.15f, 0.7f, 0.0f);
	leftUpperLeg->Rotate(leftUpperLegRotation[0], leftUpperLegRotation[1], leftUpperLegRotation[2]);
	leftLowerLeg->Rotate(leftLowerLegRotation[0], leftLowerLegRotation[1], leftLowerLegRotation[2]);
	leftFoot->Rotate(leftFootRotation[0], leftFootRotation[1], leftFootRotation[2], 0.0f, 0.2f, 0.0f);

	//===========================
	// Right Leg
	//===========================
	rightLegFrontArmor->Rotate(rightLegFrontArmorRotation[0], rightLegFrontArmorRotation[1], rightLegFrontArmorRotation[2], 0.0f, 0.7f, 0.15f);
	rightLegBackArmor->Rotate(rightLegBackArmorRotation[0], rightLegBackArmorRotation[1], rightLegBackArmorRotation[2], 0.0f, 0.7f, -0.15f);
	rightLegSideArmor->Rotate(rightLegSideArmorRotation[0], rightLegSideArmorRotation[1], rightLegSideArmorRotation[2], 0.15f, 0.7f, 0.0f);
	rightUpperLeg->Rotate(rightUpperLegRotation[0], rightUpperLegRotation[1], rightUpperLegRotation[2]);
	rightLowerLeg->Rotate(rightLowerLegRotation[0], rightLowerLegRotation[1], rightLowerLegRotation[2]);
	rightFoot->Rotate(rightFootRotation[0], rightFootRotation[1], rightFootRotation[2], 0.0f, 0.2f, 0.0f);

	//===========================
	// Draw
	//===========================
	root->Draw();
}

void BackBone::SetState(AnimState newState) {
	currentState = newState;
	animTime = 0.0f;
	//====================
	// Main Movement and rotation
	//====================
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 0.0f;
	rotation[0] = 0.0f;
	rotation[1] = 0.0f;
	rotation[2] = 0.0f;

	//====================
	// Head Rotation
	//====================
	headRotation[0] = 0.0f;
	headRotation[1] = 0.0f;
	headRotation[2] = 0.0f;

	//====================
	// Body Rotation
	//====================
	bodyRotation[0] = 0.0f;
	bodyRotation[1] = 0.0f;
	bodyRotation[2] = 0.0f;

	//====================
	// Pelvis
	//====================
	pelvisRotation[0] = 0.0f;
	pelvisRotation[1] = 0.0f;
	pelvisRotation[2] = 0.0f;

	//====================
	// Left Arm
	//====================
	leftUpperArmRotation[0] = 0.0f;
	leftUpperArmRotation[1] = 0.0f;
	leftUpperArmRotation[2] = 0.0f;
	leftUpperArmJointArmorRotation[0] = 0.0f;
	leftUpperArmJointArmorRotation[1] = 0.0f;
	leftUpperArmJointArmorRotation[2] = 0.0f;
	leftForearmRotation[0] = 0.0f;
	leftForearmRotation[1] = 0.0f;
	leftForearmRotation[2] = 0.0f;
	leftHandRotation[0] = 0.0f;
	leftHandRotation[1] = 0.0f;
	leftHandRotation[2] = 0.0f;

	//====================
	// Right Arm
	//====================
	rightUpperArmRotation[0] = 0.0f;
	rightUpperArmRotation[1] = 0.0f;
	rightUpperArmRotation[2] = 0.0f;
	rightUpperArmJointArmorRotation[0] = 0.0f;
	rightUpperArmJointArmorRotation[1] = 0.0f;
	rightUpperArmJointArmorRotation[2] = 0.0f;
	rightForearmRotation[0] = 0.0f;
	rightForearmRotation[1] = 0.0f;
	rightForearmRotation[2] = 0.0f;
	rightHandRotation[0] = 0.0f;
	rightHandRotation[1] = 0.0f;
	rightHandRotation[2] = 0.0f;

	//====================
	// Left Leg
	//====================
	leftLegFrontArmorRotation[0] = 0.0f;
	leftLegFrontArmorRotation[1] = 0.0f;
	leftLegFrontArmorRotation[2] = 0.0f;
	leftLegBackArmorRotation[0] = 0.0f;
	leftLegBackArmorRotation[1] = 0.0f;
	leftLegBackArmorRotation[2] = 0.0f;
	leftLegSideArmorRotation[0] = 0.0f;
	leftLegSideArmorRotation[1] = 0.0f;
	leftLegSideArmorRotation[2] = 0.0f;
	leftUpperLegRotation[0] = 0.0f;
	leftUpperLegRotation[1] = 0.0f;
	leftUpperLegRotation[2] = 0.0f;
	leftLowerLegRotation[0] = 0.0f;
	leftLowerLegRotation[1] = 0.0f;
	leftLowerLegRotation[2] = 0.0f;
	leftFootRotation[0] = 0.0f;
	leftFootRotation[1] = 0.0f;
	leftFootRotation[2] = 0.0f;

	//====================
	// Right Leg
	//====================
	rightLegFrontArmorRotation[0] = 0.0f;
	rightLegFrontArmorRotation[1] = 0.0f;
	rightLegFrontArmorRotation[2] = 0.0f;
	rightLegBackArmorRotation[0] = 0.0f;
	rightLegBackArmorRotation[1] = 0.0f;
	rightLegBackArmorRotation[2] = 0.0f;
	rightLegSideArmorRotation[0] = 0.0f;
	rightLegSideArmorRotation[1] = 0.0f;
	rightLegSideArmorRotation[2] = 0.0f;
	rightUpperLegRotation[0] = 0.0f;
	rightUpperLegRotation[1] = 0.0f;
	rightUpperLegRotation[2] = 0.0f;
	rightLowerLegRotation[0] = 0.0f;
	rightLowerLegRotation[1] = 0.0f;
	rightLowerLegRotation[2] = 0.0f;
	rightFootRotation[0] = 0.0f;
	rightFootRotation[1] = 0.0f;
	rightFootRotation[2] = 0.0f;

	//====================
	// Right Finger
	//====================
	rightIndexBaseRot = 0.0f;
	rightIndexMidRot = 0.0f;
	rightIndexTipRot = 0.0f;
	rightMiddleBaseRot = 0.0f;
	rightMiddleMidRot = 0.0f;
	rightMiddleTipRot = 0.0f;
	rightRingBaseRot = 0.0f;
	rightRingMidRot = 0.0f;
	rightRingTipRot = 0.0f;
	rightLittleBaseRot = 0.0f;
	rightLittleMidRot = 0.0f;
	rightLittleTipRot = 0.0f;
	rightThumbMidRot = 0.0f;
	rightThumbTipRot = 0.0f;
	rightThumbSpreadRot = 30.0f;

	//====================
	// Left Finger
	//====================
	leftIndexBaseRot = 0.0f;
	leftIndexMidRot = 0.0f;
	leftIndexTipRot = 0.0f;
	leftMiddleBaseRot = 0.0f;
	leftMiddleMidRot = 0.0f;
	leftMiddleTipRot = 0.0f;
	leftRingBaseRot = 0.0f;
	leftRingMidRot = 0.0f;
	leftRingTipRot = 0.0f;
	leftLittleBaseRot = 0.0f;
	leftLittleMidRot = 0.0f;
	leftLittleTipRot = 0.0f;
	leftThumbMidRot = 0.0f;
	leftThumbTipRot = 0.0f;
	leftThumbSpreadRot = 30.0f;
}

AnimState BackBone::GetState()
{
	return currentState;
}

// ======================================================
// Animation Update Function
// ======================================================
void BackBone::Animate(float deltaTime) {
	animTime += deltaTime * 5.0f;

	float rSpeed = animTime * 0.1f;
	const float OPPOSITE_PHASE = 3.14159f;

	switch (currentState) {
	// ==================================================
	// IDLE
	// ==================================================
	case IDLE:
		RotateBody(sin(animTime * 0.5f) * 2.0f, 0, 0);

		RotateLeftUpperArm(sin(animTime * 0.5f) * 2.0f, 0, 10);
		RotateRightUpperArm(sin(animTime * 0.5f) * 2.0f, 0, 10);

		RotateLeftHandFinger(0, 0, 0);
		RotateRightHandFinger(0, 0, 0);
		RotateLeftUpperLeg(0, 0, 0);
		RotateRightUpperLeg(0, 0, 0);
		RotateLeftLowerLeg(0);
		RotateRightLowerLeg(0);
		break;

	// ==================================================
	// WALK 
	// ==================================================
	case WALK:
		RotateLeftUpperLeg(sin(animTime) * 30.0f, 0, 0);
		RotateRightUpperLeg(sin(animTime + OPPOSITE_PHASE) * 30.0f, 0, 0);

		RotateLeftLowerLeg(clamp(sin(animTime) * 50.0f, -60.0f, 0.0f));
		RotateRightLowerLeg(clamp(sin(animTime + OPPOSITE_PHASE) * 50.0f, -60.0f, 0.0f));

		RotateLeftUpperArm(sin(animTime + OPPOSITE_PHASE) * 25.0f, 0, 10);
		RotateRightUpperArm(sin(animTime) * 25.0f, 0, 10);

		RotateLeftForearm(15.0f + sin(animTime + OPPOSITE_PHASE) * 10.0f, 0.0f);
		RotateRightForearm(15.0f + sin(animTime) * 10.0f, 0.0f);

		RotateLeftHand(sin(animTime + OPPOSITE_PHASE) * 15.0f, 0, 0);
		RotateRightHand(sin(animTime) * 15.0f, 0, 0);
		RotateRightHandFinger(90, 90, 90);
		RotateLeftHandFinger(90, 90, 90);

		break;

	// ==================================================
	//  RUN
	// ==================================================
	case RUN:
	{
		float rSpeed = animTime * 1.8f;
		float pi = 3.14159f;

		RotateBody(20.0f + sin(rSpeed * 2.0f) * 2.0f, 0, sin(rSpeed) * 5.0f);

		RotateLeftUpperLeg(sin(rSpeed) * 50.0f, 0, 0);
		RotateRightUpperLeg(sin(rSpeed + pi) * 50.0f, 0, 0);

		RotateLeftLowerLeg(clamp(-35.0f - cos(rSpeed + 0.2f) * 55.0f, -80.0f, 0.0f));
		RotateRightLowerLeg(clamp(-35.0f - cos(rSpeed + pi + 0.2f) * 55.0f, -80.0f, 0.0f));

		RotateLeftFoot(sin(rSpeed) * 30.0f - 15.0f, 0, 0);
		RotateRightFoot(sin(rSpeed + pi) * 30.0f - 15.0f, 0, 0);

		RotateLeftUpperArm(-15.0f + sin(rSpeed + pi) * 45.0f, 0, 25);
		RotateRightUpperArm(-15.0f + sin(rSpeed) * 45.0f, 0, 25);

		RotateLeftForearm(100.0f + sin(rSpeed + pi) * 20.0f, 0.0f);
		RotateRightForearm(100.0f + sin(rSpeed) * 20.0f, 0.0f);

		RotateLeftHand(sin(rSpeed + pi) * 30.0f, 0, 0);
		RotateRightHand(sin(rSpeed) * 30.0f, 0, 0);

		RotateLeftHandFinger(90, 90, 90);
		RotateRightHandFinger(90, 90, 90);
		break;
	}

	// ==========================================
	// JUMP
	// ==========================================
	case JUMP:
	{
		float jumpSpeed = animTime * 1.0f;
		float jPhase = -sin(jumpSpeed);

		if (jPhase > 0) {
			position[1] = jPhase * 4.5f;

			RotateBody(-10.0f * jPhase, 0, 0);

			RotateLeftUpperLeg(-10.0f * jPhase, 0, 0);
			RotateRightUpperLeg(-10.0f * jPhase, 0, 0);

			RotateLeftLowerLeg(-5.0f);
			RotateRightLowerLeg(-5.0f);

			RotateLeftFoot(45.0f * jPhase, 0, 0);
			RotateRightFoot(45.0f * jPhase, 0, 0);
		}
		else {
			position[1] = jPhase * 1.5f;

			RotateBody(30.0f * abs(jPhase), 0, 0);

			RotateLeftUpperLeg(abs(jPhase) * 60.0f, 0, 0);
			RotateRightUpperLeg(abs(jPhase) * 60.0f, 0, 0);

			RotateLeftLowerLeg(-abs(jPhase) * 90.0f);
			RotateRightLowerLeg(-abs(jPhase) * 90.0f);

			RotateLeftFoot(abs(jPhase) * -30.0f, 0, 0);
			RotateRightFoot(abs(jPhase) * -30.0f, 0, 0);
		}

		RotateLeftUpperArm(45.0f - jPhase * 90.0f, 0, 10);
		RotateRightUpperArm(45.0f - jPhase * 90.0f, 0, 10);

		RotateLeftForearm(30.0f, 0);
		RotateRightForearm(30.0f, 0);

		RotateLeftHandFinger(90, 90, 90);
		RotateRightHandFinger(90, 90, 90);

		break;
	}

	// ==================================================
	// ATTACK
	// ==================================================
	case ATTACK:
	{
		float aSpeed = animTime * 1.0f;
		float swing = -sin(aSpeed);

		RotateBody(10.0f + swing * 20.0f, swing * 40.0f, 0);

		RotateLeftUpperLeg(-10.0f, 15.0f - swing * 15.0f, 25.0f);
		RotateRightUpperLeg(40.0f + swing * 10.0f, 0.0f, 25.0f);
		RotateLeftLowerLeg(-45.0f);
		RotateRightLowerLeg(-30.0f - swing * 10.0f);
		RotateLeftFoot(10.0f, 0, 0);
		RotateRightFoot(0.0f, 0, 0);

		RotateRightUpperArm(-60.0f + swing * 80.0f, swing * 45.0f, 10.0f);

		RotateRightForearm(50.0f - swing * 10.0f, swing * 10.0f);

		RotateRightHand(-30.0f, 0, 0);

		RotateLeftUpperArm(80.0f, 0, 20.0f);
		RotateLeftForearm(60.0f, 30.0f);
		RotateLeftHand(0.0f, 0.0f, swing * 30.0f);

		RotateRightHandFinger(90, 90, 90);
		RotateLeftHandFinger(90, 90, 90);
	}
	break;
	break;
	}
}