#pragma once
#include "Actor.h"
#include "SoundEvent.h"

class FPSActor : public Actor
{
public:
	FPSActor(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keys) override;

	void SetFootStepSurface(float value);
	void SetVisible(bool visible);

private:
	class MoveComponent* mMoveComp;

};

