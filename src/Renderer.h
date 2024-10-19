#pragma once

#include <GL/glew.h>
#include "iostream"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
void PrintShaderLog(unsigned int shader);
void PrintProgramLog(int prog);
bool CheckOpenGLError();

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader) const;
	void DrawWithoutIBO(const VertexArray& VAO, const Shader& shader) const;
};