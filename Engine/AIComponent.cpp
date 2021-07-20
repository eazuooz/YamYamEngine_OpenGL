#include "AIComponent.h"

AIComponent::AIComponent(Actor* owner)
	:Component(owner)
	, mCurrentState(nullptr)
{
}

void AIComponent::Update(float deltaTime)
{
}

void AIComponent::ChangeState(const std::string& name)
{
}

void AIComponent::RegisterState(AIState* state)
{
}
