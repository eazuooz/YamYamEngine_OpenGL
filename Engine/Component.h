#pragma once
#include "Math.h"
#include <rapidjson/document.h>

class Transform;
class Actor;
class Component //: public Object
{
public:
	enum TypeID
	{
		TComponent = 0,
		TTransformComponent,
		TAudioComponent,
		TBallMove,
		TBoxComponent,
		TCameraComponent,
		TFollowCamera,
		TMeshComponent,
		TMoveComponent,
		TSkeletalMeshComponent,
		TSpriteComponent,
		TMirrorCamera,
		TPointLightComponent,
		TTargetComponent,

		NUM_COMPONENT_TYPES
	};

	static const char* TypeNames[NUM_COMPONENT_TYPES];

	// Constructor
	// (the lower the update order, the earlier the component updates)
	Component(class Actor* owner, int updateOrder = 100);
	// Destructor
	virtual ~Component();
	// Update this component by delta time
	virtual void Update(float deltaTime);
	// Process input for this component
	virtual void ProcessInput(const uint8_t* keyState) {}
	// Called when world transform changes
	virtual void OnUpdateWorldTransform();

	//test
	virtual void init() {};
	virtual void start() {};
	virtual void preUpdate() {};
	virtual void update(float dt) {};
	virtual void postUpdate() {};
	virtual void renderPreUpdate() {};
	virtual void renderUpdate() {};
	virtual void renderPostUpdate() {};
	virtual void stop() {};
	//virtual void onSceneChanged();

	Actor* GetOwner() { return mOwner; }
	int GetUpdateOrder() const { return mUpdateOrder; }

	virtual TypeID GetType() const = 0;

	// Load/Save
	virtual void LoadProperties(const rapidjson::Value& inObj);
	virtual void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const;

	// Create a component with specified properties
	template <typename T>
	static Component* Create(Actor* actor, const rapidjson::Value& inObj)
	{
		// Dynamically allocate component of type T
		T* t = new T(actor);
		// Call LoadProperties on new component
		t->LoadProperties(inObj);
		return t;
	}

	//template<class T> T* getComponent()
	//{
	//	T* component;
	//	for (auto& c : mOwner->GetComponents())
	//	{
	//		if ((component = dynamic_cast<T*>) != nullptr)
	//		{
	//			return component;
	//		}
	//	}
	//	return nullptr;
	//}

protected:
	// Owning actor
	Actor* mOwner;
	// Update order of component
	int mUpdateOrder;
	// Transform component
	Transform* mTransform;
};
