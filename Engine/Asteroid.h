#pragma once
#include "Actor.h"
class Asteroid : public Actor
{
public:
	Asteroid(class Game* game);
	~Asteroid();

	void UpdateActor(float deltaTime) override;

	class CircleComponent* GetCircle() { return mCircle; }
private:
	class CircleComponent* mCircle;
	float rotation;
};
