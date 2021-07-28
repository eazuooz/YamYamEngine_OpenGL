#pragma once
#include "Component.h"
#include <cstddef>

class MeshComponent : public Component
{
public:
	MeshComponent(class Actor* owner);
	~MeshComponent();
	// Draw this mesh component
	virtual void Draw(class Shader* shader);
	// Set the mesh/texture index used by mesh component
	virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }
	void SetTextureIndex(size_t index) { mTextureIndex = index; }

	void Update(float deltaTime) override;
protected:
	class Mesh* mMesh;
	size_t mTextureIndex;
};