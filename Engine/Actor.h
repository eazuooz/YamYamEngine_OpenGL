

#pragma once
#include <vector>
#include "Math.h"
#include <rapidjson/document.h>
#include "Component.h"
#include "Transform.h"

class Game;
class Actor
{
public:
	enum TypeID
	{
		TActor = 0,
		TBallActor,
		TFollowActor,
		TPlaneActor,
		TTargetActor,

		NUM_ACTOR_TYPES
	};

	static const char* TypeNames[NUM_ACTOR_TYPES];

	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(Game* game);
	virtual ~Actor();

	bool Init();
	void Start();
	void PreUpdate(float deltaTime);
	
	// Update function called from Game (not overridable)
	void Update(float deltaTime);

	void PostUpdate(float deltaTime);
	void RenderPreUpdate();
	void RenderUpdate();
	void RenderPostUpdate();
	void Stop();
	
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);
	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const uint8_t* keyState);
	// Any actor-specific input code (overridable)
	virtual void ActorInput(const uint8_t* keyState);

	void ComputeWorldTransform();

	// Transform Getters/setters
	Transform* GetTransform() { return mTransform; }
	Game* GetGame() { return mGame; }

	
	//const Vector3& GetPosition() const { return mPosition; }
	//void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeTransform = true; }
	//float GetScale() const { return mScale; }
	//void SetScale(float scale) { mScale = scale; mRecomputeTransform = true; }
	//const Quaternion& GetRotation() const { return mRotation; }
	//void SetRotation(const Quaternion& rotation) { mRotation = rotation;   mRecomputeTransform = true; }
	//const Matrix4& GetWorldTransform() const { return mWorldTransform; }
	//Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }
	//Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, mRotation); }
	
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	
	virtual TypeID GetType() const { return TActor; }

	const std::vector<Component*>& GetComponents() const { return mComponents; }

	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	template<class T> 
	T* GetComponent()
	{
		T* component;
		for (auto c : mComponents)
		{
			component = dynamic_cast<T*>(c);
			if (component != nullptr)
			{
				return component;
			}
		}
		return nullptr;
	}
	// Search throuch component vector for one of type
	Component* GetComponentOfType(Component::TypeID type)
	{
		Component* comp = nullptr;
		for (Component* c : mComponents)
		{
			if (c->GetType() == type)
			{
				comp = c;
				break;
			}
		}
		return comp;
	}

	// Load/Save
	virtual void LoadProperties(const rapidjson::Value& inObj);
	virtual void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const;

	// Create an actor with specified properties
	template <typename T>
	static Actor* Create(class Game* game, const rapidjson::Value& inObj)
	{
		// Dynamically allocate actor of type T
		T* t = new T(game);
		// Call LoadProperties on new actor
		t->LoadProperties(inObj);
		return t;
	}



private:
	// Actor's state
	Game* mGame;
	State mState;
	Transform* mTransform;
	
	std::vector<Component*> mComponents;

	//// Transform
	//Matrix4 mWorldTransform;
	//Vector3 mPosition;
	//Quaternion mRotation;
	//float mScale;
	//bool mRecomputeTransform;

};
