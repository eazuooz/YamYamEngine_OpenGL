#include "Transform.h"
#include "Actor.h"

Transform::Transform(Actor* owner)
	:Component(owner)
	, mPosition(Vector3::Zero)
	, mRotation(Quaternion::Identity)
	, mScale(1.0f)
	, mRecomputeTransform(true)
{
	
}

Transform::~Transform()
{
}

void Transform::ComputeWorldTransform()
{
	mRecomputeTransform = false;
	// Scale, then rotate, then translate
	mWorldTransform = Matrix4::CreateScale(mScale);
	mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
	mWorldTransform *= Matrix4::CreateTranslation(mPosition);
}

void Transform::RotateToNewForward(const Vector3& forward)
{
	// Figure out difference between original (unit x) and new
	float dot = Vector3::Dot(Vector3::UnitX, forward);
	float angle = Math::Acos(dot);
	// Facing down X
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::Identity);
	}
	// Facing down -X
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		// Rotate about axis from cross product
		Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}
