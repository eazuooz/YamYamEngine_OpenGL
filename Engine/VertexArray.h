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
	// ���ؽ� ���ۿ� �����ϴ� ���ؽ��� ��
	unsigned int mNumVerts;
	// �ε��� ���ۿ� �����ϴ� �ε����� ��
	unsigned int mNumIndices;
	// ���ؽ� ������ OPENGL ID
	unsigned int mVertexBuffer;
	// �ε��� ������ OPENGL ID
	unsigned int mIndexBuffer;
	// ���ý� �迭 ��ü�� OPNGL ID
	unsigned int mVertexArray;
};

