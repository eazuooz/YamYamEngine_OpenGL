#pragma once
#include <vector>
#include <string>

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Load(const std::string& fileName, class Renderer* renderer);
	void Unload();
	
	class VertexArray* GetVertexArray() { return mVertexArray; }
	class Texture* GetTexture(size_t index);
	const std::string& GetShaderName() const { return mShaderName; }
	float GetRadius() const { return mRadius; }
	float GetSpecPower() const { return mSpecPower; }

private:
	std::vector<class Texture*> mTextures;
	class VertexArray* mVertexArray;
	std::string mShaderName;
	float mRadius;
	float mSpecPower;
};

