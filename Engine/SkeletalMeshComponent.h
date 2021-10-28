

#pragma once
#include "MeshComponent.h"
#include "MatrixPalette.h"

class SkeletalMeshComponent : public MeshComponent
{
public:
	SkeletalMeshComponent(class Actor* owner);
	// Draw this mesh component
	void Draw(class Shader* shader) override;

	void Update(float deltaTime) override;

	// Setters
	void SetSkeleton(class Skeleton* sk) { mSkeleton = sk; }

	// Play an animation. Returns the length of the animation
	float PlayAnimation(class Animation* anim, float playRate = 1.0f);

	TypeID GetType() const override { return TSkeletalMeshComponent; }

	void LoadProperties(const rapidjson::Value& inObj) override;
	void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const override;
protected:
	void ComputeMatrixPalette();

	MatrixPalette mPalette;
	class Skeleton* mSkeleton;
	class Animation* mAnimation;
	float mAnimPlayRate;
	float mAnimTime;
};
