#pragma once
#include "pch.h"
#include "Object.h"
enum AnimState {
	IDLE,
	WALK,
	ATTACK,
	RUN,
	JUMP
};

class BackBone
{
public:
	// animation
	
	void Animate(float deltaTime);
	void SetState(AnimState newState);
	AnimState GetState();

	Object* root = new Object("empty.json");
	// head
	Object* headBone = new Object("head.json");

	// body
	Object* body = new Object("body.json");
	Object* wing = new Object("wing.json");
	Object* pelvis = new Object("bodyBone.json");

	// arms and hands
	Object* leftUpperArm = new Object("empty.json");
	Object* leftUpperArmJoint = new Object("empty.json");
	Object* leftUpperArmJointOuter = new Object("armJointArmor.json");
	Object* leftUpperArmOuter = new Object("upperArmOuter.json");
	Object* leftForearm = new Object("empty.json");
	Object* leftForearmOuter = new Object("forearmOuter.json");
	Object* leftHand = new Object("handPalm.json");
	Object* rightUpperArm = new Object("empty.json");
	Object* rightUpperArmJoint = new Object("empty.json");
	Object* rightUpperArmJointOuter = new Object("armJointArmor.json");
	Object* rightUpperArmOuter = new Object("upperArmOuter.json");
	Object* rightForearm = new Object("empty.json");
	Object* rightForearmOuter = new Object("forearmOuter.json");
	Object* rightHand = new Object("handPalm.json");
	Object* rightIndexBase = new Object("handFinger.json");
	Object* rightIndexMid = new Object("handFinger.json");
	Object* rightIndexTip = new Object("handFinger.json");
	Object* rightMiddleBase = new Object("handFinger.json");
	Object* rightMiddleMid = new Object("handFinger.json");
	Object* rightMiddleTip = new Object("handFinger.json");
	Object* rightRingBase = new Object("handFinger.json");
	Object* rightRingMid = new Object("handFinger.json");
	Object* rightRingTip = new Object("handFinger.json");
	Object* rightLittleBase = new Object("handFinger.json");
	Object* rightLittleMid = new Object("handFinger.json");
	Object* rightLittleTip = new Object("handFinger.json");
	Object* rightThumbSpread = new Object("empty.json");
	Object* rightThumbMid = new Object("handFinger.json");
	Object* rightThumbTip = new Object("handFinger.json");
	Object* leftIndexBase = new Object("handFinger.json");
	Object* leftIndexMid = new Object("handFinger.json");
	Object* leftIndexTip = new Object("handFinger.json");
	Object* leftMiddleBase = new Object("handFinger.json");
	Object* leftMiddleMid = new Object("handFinger.json");
	Object* leftMiddleTip = new Object("handFinger.json");
	Object* leftRingBase = new Object("handFinger.json");
	Object* leftRingMid = new Object("handFinger.json");
	Object* leftRingTip = new Object("handFinger.json");
	Object* leftLittleBase = new Object("handFinger.json");
	Object* leftLittleMid = new Object("handFinger.json");
	Object* leftLittleTip = new Object("handFinger.json");
	Object* leftThumbSpread = new Object("empty.json");
	Object* leftThumbMid = new Object("handFinger.json");
	Object* leftThumbTip = new Object("handFinger.json");

	// legs
	Object* leftLegFrontArmor = new Object("leftLegFrontArmor.json");
	Object* leftLegBackArmor = new Object("leftLegBackArmor.json");
	Object* leftLegSideArmor = new Object("leftLegSideArmor.json");
	Object* leftUpperLeg = new Object("leftUpperLeg.json");
	Object* leftLowerLeg = new Object("leftLowerLeg.json");
	Object* leftFoot = new Object("leftFoot.json");

	Object* rightLegFrontArmor = new Object("rightLegFrontArmor.json");
	Object* rightLegBackArmor = new Object("rightLegBackArmor.json");
	Object* rightLegSideArmor = new Object("rightLegSideArmor.json");
	Object* rightUpperLeg = new Object("rightUpperLeg.json");
	Object* rightLowerLeg = new Object("rightLowerLeg.json");
	Object* rightFoot = new Object("rightFoot.json");

	// Weapons
	Object* gun = new Object("gun.json");
	Object* sword = new Object("sword.json");
	Object* shield = new Object("shield.json");

	~BackBone();

	void SetBone();
	void ReadData();
	void Draw();
	//==============
	// body movement
	//==============
	void Move(float x, float y, float z);
	void Rotate(float x, float y, float z);
	/**
	 * @brief Rotate Head
	 *
	 * @param x: -40 to 40
	 * @param y: -70 to 70
	 * @param z: -30 to 30
	 */
	void RotateHead(float x, float y, float z);
	/**
	 * @brief Rotate Body
	 *
	 * @param x: -30 to 30
	 * @param y: -45 to 45
	 * @param z: -20 to 20
	 */
	void RotateBody(float x, float y, float z);
	/**
	 * @brief Rotate Pelvis
	 *
	 * @param x: -20 to 20
	 * @param y: -20 to 20
	 * @param z: -15 to 15
	 */
	void RotatePelvis(float x, float y, float z);

	//====================
	// upper part movement
	//====================
	/**
	 * @brief Rotate Left Upper Arm
	 *
	 * @param x: -45 to 180
	 * @param y: -20 to 100
	 * @param z: -90 to 90
	 */
	void RotateLeftUpperArm(float x, float y, float z);
	/**
	 * @brief Rotate Left Fore Arm
	 *
	 * @param x: 0 to 140
	 * @param y: -90 to 90
	 */
	void RotateLeftForearm(float x, float y);
	/**
	 * @brief Rotate Left Hand
	 *
	 * @param x: -45 to 45
	 * @param y: -30 to 30
	 * @param z: -45 to 45
	 */
	void RotateLeftHand(float x, float y, float z);
	/**
	 * @brief Rotate Right Upper Arm
	 *
	 * @param x: -45 to 180
	 * @param y: -20 to 100
	 * @param z: -90 to 90
	 */
	void RotateRightUpperArm(float x, float y, float z);
	/**
	 * @brief Rotate Right Fore Arm
	 *
	 * @param x: 0 to 140
	 * @param y: -90 to 90
	 */
	void RotateRightForearm(float x, float y);
	/**
	 * @brief Rotate Right Hand
	 *
	 * @param x: -45 to 45
	 * @param y: -30 to 30
	 * @param z: -45 to 45
	 */
	void RotateRightHand(float x, float y, float z);
	//====================
	// lower part movement
	//====================
	/**
	 * @brief Rotate Left Upper Leg
	 *
	 * @param x: -120 to 90
	 * @param y: -15 to 60
	 * @param z: -45 to 45
	 */
	void RotateLeftUpperLeg(float x, float y, float z);
	/**
	 * @brief Rotate Left Lower Leg
	 *
	 * @param x: -130 to 0
	 */
	void RotateLeftLowerLeg(float x);
	/**
	 * @brief Rotate Left Foot
	 *
	 * @param x: -30 to 45
	 * @param y: -30 to 30
	 * @param z: -15 to 15
	 */
	void RotateLeftFoot(float x, float y, float z);
	/**
	 * @brief Rotate Right Upper Leg
	 *
	 * @param x: -120 to 90
	 * @param y: -15 to 60
	 * @param z: -45 to 45
	 */
	void RotateRightUpperLeg(float x, float y, float z);
	/**
	 * @brief Rotate Right Lower Leg
	 *
	 * @param x: -130 to 0
	 */
	void RotateRightLowerLeg(float x);
	/**
	 * @brief Rotate Right Foot
	 *
	 * @param x: -30 to 45
	 * @param y: -30 to 30
	 * @param z: -15 to 15
	 */
	void RotateRightFoot(float x, float y, float z);

	/**
	 * @brief Rotate Right Hand Finger
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateRightHandFinger(float base, float mid, float tip);
	/**
	 * @brief Rotate Right Index
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateRightIndex(float base, float mid, float tip);
	/**
	 * @brief Rotate Right Middle
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateRightMiddle(float base, float mid, float tip);
	/**
	 * @brief Rotate Right Ring
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateRightRing(float base, float mid, float tip);
	/**
	 * @brief Rotate Right Little
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateRightLittle(float base, float mid, float tip);
	/**
	 * @brief Rotate Right Thumb
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateRightThumb(float base, float mid, float tip);

	/**
	 * @brief Rotate Right Hand Finger
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateLeftHandFinger(float base, float mid, float tip);
	/**
	 * @brief Rotate Right Index
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateLeftIndex(float base, float mid, float tip);
	/**
	 * @brief Rotate Right Middle
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateLeftMiddle(float base, float mid, float tip);
	/**
	 * @brief Rotate Right Ring
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateLeftRing(float base, float mid, float tip);
	/**
	 * @brief Rotate Right Little
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateLeftLittle(float base, float mid, float tip);
	/**
	 * @brief Rotate Right Thumb
	 *
	 * @param x: 0 to 90
	 * @param y: 0 to 90
	 * @param z: 0 to 90
	 */
	void RotateLeftThumb(float base, float mid, float tip);
private:
	float animTime = 0.0f;
	AnimState currentState = IDLE;

	// Rotation and Movement
	//====================
	// Main Movement and rotation
	//====================
	float position[3] = { 0.0f, 0.0f, 0.0f };
	float rotation[3] = { 0.0f, 0.0f, 0.0f };

	//====================
	// Head Rotation
	//====================
	float headRotation[3] = { 0.0f, 0.0f, 0.0f };

	//====================
	// Body Rotation
	//====================
	float bodyRotation[3] = { 0.0f, 0.0f, 0.0f };

	//====================
	// Pelvis
	//====================
	float pelvisRotation[3] = { 0.0f, 0.0f, 0.0f };

	//====================
	// Left Arm
	//====================
	float leftUpperArmRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftUpperArmJointArmorRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftForearmRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftHandRotation[3] = { 0.0f, 0.0f, 0.0f };

	//====================
	// Right Arm
	//====================
	float rightUpperArmRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightUpperArmJointArmorRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightForearmRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightHandRotation[3] = { 0.0f, 0.0f, 0.0f };

	//====================
	// Left Leg
	//====================
	float leftLegFrontArmorRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftLegBackArmorRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftLegSideArmorRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftUpperLegRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftLowerLegRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftFootRotation[3] = { 0.0f, 0.0f, 0.0f };

	//====================
	// Right Leg
	//====================
	float rightLegFrontArmorRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightLegBackArmorRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightLegSideArmorRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightUpperLegRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightLowerLegRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightFootRotation[3] = { 0.0f, 0.0f, 0.0f };

	//====================
	// Right Finger
	//====================
	float rightIndexBaseRot = 0.0f;
	float rightIndexMidRot = 0.0f;
	float rightIndexTipRot = 0.0f;
	float rightMiddleBaseRot = 0.0f;
	float rightMiddleMidRot = 0.0f;
	float rightMiddleTipRot = 0.0f;
	float rightRingBaseRot = 0.0f;
	float rightRingMidRot = 0.0f;
	float rightRingTipRot = 0.0f;
	float rightLittleBaseRot = 0.0f;
	float rightLittleMidRot = 0.0f;
	float rightLittleTipRot = 0.0f;
	float rightThumbMidRot = 0.0f;
	float rightThumbTipRot = 0.0f;
	float rightThumbSpreadRot = 30.0f;

	//====================
	// Left Finger
	//====================
	float leftIndexBaseRot = 0.0f;
	float leftIndexMidRot = 0.0f;
	float leftIndexTipRot = 0.0f;
	float leftMiddleBaseRot = 0.0f;
	float leftMiddleMidRot = 0.0f;
	float leftMiddleTipRot = 0.0f;
	float leftRingBaseRot = 0.0f;
	float leftRingMidRot = 0.0f;
	float leftRingTipRot = 0.0f;
	float leftLittleBaseRot = 0.0f;
	float leftLittleMidRot = 0.0f;
	float leftLittleTipRot = 0.0f;
	float leftThumbMidRot = 0.0f;
	float leftThumbTipRot = 0.0f;
	float leftThumbSpreadRot = 30.0f;
};

