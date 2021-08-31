#pragma once
#include "CameraComponent.h"

class OrbitCamera : public CameraComponent
{
public:
	OrbitCamera(class Actor* owner);

	void Update(float deltaTime) override;

	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetYawSpeed() const { return mYawSpeed; }

	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	void SetYawSpeed(float speed) { mYawSpeed = speed; }
private:
	// Offset from target
	Vector3 mOffset;
	// Up vector of camera
	Vector3 mUp;
	// Rotation/sec speed of pitch
	float mPitchSpeed;
	// Rotation/sec speed of yaw
	float mYawSpeed;
};

