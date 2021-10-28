

#pragma once
#include "Math.h"
#include "Component.h"

class PointLightComponent : public Component
{
public:
	PointLightComponent(class Actor* owner);
	~PointLightComponent();

	// Draw this point light as geometry
	void Draw(class Shader* shader, class Mesh* mesh);

	// Diffuse color
	Vector3 mDiffuseColor;
	// Radius of light
	float mInnerRadius;
	float mOuterRadius;

	TypeID GetType() const override { return TPointLightComponent; }

	void LoadProperties(const rapidjson::Value& inObj) override;
	void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const override;
};
