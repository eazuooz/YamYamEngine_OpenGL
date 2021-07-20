#pragma once
#include "Actor.h"
class Asteroid : public Actor
{
public:
	Asteroid(class Game* game);
	~Asteroid();

	class CircleComponent* GetCircle() { return mCircle; }
private:
	class CircleComponent* mCircle;
	float rotation;
};
