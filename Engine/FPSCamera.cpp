#include "FPSCamera.h"
#include "Actor.h"

FPSCamera::FPSCamera(Actor* owner)
	:CameraComponent(owner)
	, mPitchSpeed(0.0f)
	, mMaxPitch(Math::Pi / 3.0f)
	, mPitch(0.0f)
{
}

void FPSCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	Vector3 cameraPos = mOwner->GetTransform()->GetPosition();

	mPitch += mPitchSpeed * deltaTime;
	mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);

	Quaternion q(mOwner->GetTransform()->GetRight(), mPitch);

	Vector3 viewForward = Vector3::Transform(mOwner->GetTransform()->GetForward(), q);
	Vector3 target = cameraPos + viewForward * 100.0f;
	Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}