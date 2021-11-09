

#pragma once
#include "Actor.h"

class PlaneActor : public Actor
{
public:
	PlaneActor(class Game* game);
	TypeID GetType() const override { return TPlaneActor; }
};
