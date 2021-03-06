

#include "BallMove.h"
#include "Actor.h"
#include "Game.h"
#include "PhysWorld.h"
#include "TargetActor.h"
#include "BallActor.h"

BallMove::BallMove(Actor* owner)
	:MoveComponent(owner)
{
}

void BallMove::Update(float deltaTime)
{
	const float segmentLength = 30.0f;
	PhysWorld* phys = mOwner->GetGame()->GetPhysWorld();

	// Construct segment in direction of travel
	Vector3 start = mOwner->GetTransform()->GetPosition();
	Vector3 dir = mOwner->GetTransform()->GetForward();
	Vector3 end = start + dir * segmentLength;
	// Create line segment
	LineSegment l(start, end);
	// Test segment vs world
	PhysWorld::CollisionInfo info;
	if (phys->SegmentCast(l, info))
	{
		// If we collided, reflect the ball about the normal
		dir = Vector3::Reflect(dir, info.mNormal);
		mOwner->GetTransform()->RotateToNewForward(dir);
		// Did we hit a target?
		TargetActor* target = dynamic_cast<TargetActor*>(info.mActor);
		if (target)
		{
			static_cast<BallActor*>(mOwner)->HitTarget();
		}
	}
	MoveComponent::Update(deltaTime);
}
