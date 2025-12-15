#pragma once
#include "pch.h"
#include "Object.h"

class BackBone
{
public:
	Object* root = new Object("a");
	// head
	Object* headBone = new Object("head.json");

	// body
	Object* body = new Object("body.json");
	Object* pelvis = new Object("bodyBone.json");

	// arms and hands
	Object* leftUpperArm = new Object("bodyBone.json");
	Object* leftForearm = new Object("bodyBone.json");
	Object* leftHand = new Object("handFinger.json");
	Object* rightUpperArm = new Object("bodyBone.json");
	Object* rightForearm = new Object("bodyBone.json");
	Object* rightHand = new Object("handFinger.json");

	// legs
	Object* leftUpperLeg = new Object("leftUpperLeg.json");
	Object* leftLowerLeg = new Object("leftLowerLeg.json");
	Object* leftFoot = new Object("leftFoot.json");
	Object* rightUpperLeg = new Object("bodyBone.json");
	Object* rightLowerLeg = new Object("bodyBone.json");
	Object* rightFoot = new Object("handFinger.json");

	// Rotation and Movement
	float position[3] = { 0.0f, 0.0f, 0.0f };
	float rotation[3] = { 0.0f, 0.0f, 0.0f };
	float headRotation[3] = { 0.0f, 0.0f, 0.0f };
	float bodyRotation[3] = { 0.0f, 0.0f, 0.0f };
	float pelvisRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftUpperArmRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftForearmRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftHandRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightUpperArmRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightForearmRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightHandRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftUpperLegRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftLowerLegRotation[3] = { 0.0f, 0.0f, 0.0f };
	float leftFootRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightUpperLegRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightLowerLegRotation[3] = { 0.0f, 0.0f, 0.0f };
	float rightFootRotation[3] = { 0.0f, 0.0f, 0.0f };

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
	 * @param x: -60 to 90
	 * @param y: -45 to 45
	 * @param z: -30 to 30
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
	 * @param x: -135 to 45
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
	 * @param x: -45 to 90
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
	 * @param x: -90 to 45
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
};

