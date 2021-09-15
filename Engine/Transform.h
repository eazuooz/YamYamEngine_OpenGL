#pragma once
#include "Component.h"


class Transform : public Component
{
public:
	Transform(class Actor* owner);
	~Transform();

	TypeID GetType() const override { return TTransformComponent; }

public:
	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeTransform = true; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; mRecomputeTransform = true; }
	const Quaternion& GetRotation() const { return mRotation; }
	void SetRotation(const Quaternion& rotation) { mRotation = rotation;   mRecomputeTransform = true; }
	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, mRotation); }
	void RotateToNewForward(const Vector3& forward);
	bool GetRecomputeTransform() { return mRecomputeTransform; }

private:
	Matrix4 mWorldTransform;
	Vector3 mPosition;
	Quaternion mRotation;
	float mScale;
	bool mRecomputeTransform;
};

