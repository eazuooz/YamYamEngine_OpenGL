#pragma once
#include "Component.h"


class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetHorizonSpeed() const { return mHorizonSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void SetHorizonSpeed(float speed) { mHorizonSpeed = speed; }

private:
	float mAngularSpeed;
	float mForwardSpeed;
	float mHorizonSpeed;
};

