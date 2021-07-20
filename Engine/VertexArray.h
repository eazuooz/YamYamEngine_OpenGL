#pragma once

class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	// Activate this vertex array (so we can draw it)
	void SetActive();

	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	// 버텍스 버퍼에 존재하는 버텍스의 수
	unsigned int mNumVerts;
	// 인덱스 버퍼에 존재하는 인데스의 수
	unsigned int mNumIndices;
	// 버텍스 버퍼의 OPENGL ID
	unsigned int mVertexBuffer;
	// 인덱스 버퍼의 OPENGL ID
	unsigned int mIndexBuffer;
	// 버택스 배열 객체의 OPNGL ID
	unsigned int mVertexArray;
};

