#pragma once
#include <GL/glew.h>
#include <string>
#include "Math.h"

class Shader
{
public:
	Shader();
	~Shader();
	// Load the vertex/fragment shaders with the given names
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	// Set this as the active shader program
	void SetActive();
	// Sets a Matrix uniform
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
	// Sets a Vector3 uniform
	void SetVectorUniform(const char* name, const Vector3& vector);
	// Sets a float uniform
	void SetFloatUniform(const char* name, float value);
private:
	// Tries to compile the specified shader
	bool CompileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);

	// Tests whether shader compiled successfully
	bool IsCompiled(GLuint shader);
	// Tests whether vertex/fragment programs link
	bool IsValidProgram();
private:
	// Store the shader object IDs
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};

