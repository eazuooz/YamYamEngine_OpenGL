
#pragma once
#include "Component.h"
#include "Math.h"

class CameraComponent : public Component
{
public:
	CameraComponent(class Actor* owner, int updateOrder = 200);

	TypeID GetType() const override { return TCameraComponent; }
protected:
	void SetViewMatrix(const Matrix4& view);
};
