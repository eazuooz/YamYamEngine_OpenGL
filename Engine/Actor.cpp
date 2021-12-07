

#include "Actor.h"
#include "Game.h"
#include "Component.h"

#include "LevelLoader.h"

const char* Actor::TypeNames[NUM_ACTOR_TYPES] = 
{
	"Actor",
	"BallActor",
	"FollowActor",
	"PlaneActor",
	"TargetActor",
};

Actor::Actor(Game* game)
	:mState(EActive)
	,mGame(game)
{
	mGame->AddActor(this);
	
	mTransform = new Transform(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

bool Actor::Init()
{
	for (auto comp : mComponents)
	{
		comp->init();
	}

	return true;
}

void Actor::Start()
{
	for (auto comp : mComponents)
	{
		comp->start();
	}
}

void Actor::PreUpdate(float deltaTime)
{
	if (mState == EActive)
	{
		if (mTransform->GetRecomputeTransform())
		{
			ComputeWorldTransform();
		}
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateComponents(deltaTime);
	}
}

void Actor::PostUpdate(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateActor(deltaTime);
	}
}

void Actor::RenderPreUpdate()
{
	for (auto comp : mComponents)
	{
		comp->renderPreUpdate();
	}
}

void Actor::RenderUpdate()
{
	for (auto comp : mComponents)
	{
		comp->renderUpdate();
	}
}

void Actor::RenderPostUpdate()
{
	for (auto comp : mComponents)
	{
		comp->renderPostUpdate();
	}
}

void Actor::Stop()
{
	for (auto comp : mComponents)
	{
		comp->stop();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{

}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		// First process input for components
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{

}

void Actor::ComputeWorldTransform()
{
	mTransform->ComputeWorldTransform();
	//GetComponent<Transform>()->ComputeWorldTransform();

	// Inform components world transform updated
	for (auto comp : mComponents)
	{
		comp->OnUpdateWorldTransform();
	}
}

void Actor::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

void Actor::LoadProperties(const rapidjson::Value& inObj)
{
	// Use strings for different states
	std::string state;
	if (JsonHelper::GetString(inObj, "state", state))
	{
		if (state == "active")
		{
			SetState(EActive);
		}
		else if (state == "paused")
		{
			SetState(EPaused);
		}
		else if (state == "dead")
		{
			SetState(EDead);
		}
	}

	// Load position, rotation, and scale, and compute transform
	Vector3 outPos;
	JsonHelper::GetVector3(inObj, "position", outPos);
	mTransform->SetPosition(outPos);

	Quaternion outQut;
	JsonHelper::GetQuaternion(inObj, "rotation", outQut);
	mTransform->SetRotation(outQut);

	float outScale;
	JsonHelper::GetFloat(inObj, "scale", outScale);
	mTransform->SetScale(outScale);
	ComputeWorldTransform();
}

void Actor::SaveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	std::string state = "active";
	if (mState == EPaused)
	{
		state = "paused";
	}
	else if (mState == EDead)
	{
		state = "dead";
	}

	JsonHelper::AddString(alloc, inObj, "state", state);
	JsonHelper::AddVector3(alloc, inObj, "position", mTransform->GetPosition());
	JsonHelper::AddQuaternion(alloc, inObj, "rotation", mTransform->GetRotation());
	JsonHelper::AddFloat(alloc, inObj, "scale", mTransform->GetScale());
}
