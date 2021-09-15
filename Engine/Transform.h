#pragma once
#include "Component.h"


class Transform : public Component
{
public:
	Transform();
	~Transform();

	TypeID GetType() const override { return TTransformComponent; }
};

