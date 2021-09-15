#pragma once
#include "Component.h"


class Transform : public Component
{
public:
	Transform(class Actor* owner);
	~Transform();

	TypeID GetType() const override { return TTransformComponent; }

private:

};

