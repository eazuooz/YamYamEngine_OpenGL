

#pragma once
#include "Actor.h"

class TargetActor : public Actor
{
public:
	TargetActor(class Game* game);
	TypeID GetType() const override { return TTargetActor; }
};
