#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 8 * sizeof(float), verts, GL_STATIC_DRAW);
	
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);

	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
		reinterpret_cast<void*>(sizeof(float) * 3));

	//Texture uv
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
		reinterpret_cast<void*>(sizeof(float) * 6));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}
