#include "Renderer.h"
#include "Shader.h"

#include <iostream>
#include <fstream>

Shader::Shader(const std::string& vertexFile, const std::string& fragFile)
	:vShaderFilePath(vertexFile), fShaderFilePath(fragFile),shaderID(0)
{
	
	std::string vertexShaderSrc   = readShaderSource(vShaderFilePath);
	std::string fragmentShaderSrc = readShaderSource(fShaderFilePath);
	shaderID = CreateShader(vertexShaderSrc, fragmentShaderSrc);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(shaderID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(shaderID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

std::string Shader::readShaderSource(const std::string& filePath)
{

	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	std::string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

unsigned int Shader::CreateShader(const std::string& vShaderSrc, const std::string& fShaderSrc)
{
	GLCall(unsigned int shaderProgram = glCreateProgram());
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vShaderSrc);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fShaderSrc);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	GLCall(glLinkProgram(shaderProgram));
	CheckOpenGLError();
	int linked;
	GLCall(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked));
	if (linked != 1)
	{
		std::cout << "linking failed" << std::endl;
		PrintProgramLog(shaderProgram);
	}
	GLCall(glValidateProgram(shaderProgram));
	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));

	return shaderProgram;
}

unsigned int Shader::CompileShader(unsigned int shaderType, const std::string& shaderSrc)
{
	GLCall(unsigned int shader = glCreateShader(shaderType));
	const char* shaderStr = shaderSrc.c_str();
	GLCall(glShaderSource(shader, 1, &shaderStr, NULL));
	GLCall(glCompileShader(shader));
	CheckOpenGLError();
	int numCompiled;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &numCompiled));
	if (numCompiled != 1)
	{
		if (shaderType == GL_VERTEX_SHADER) 
			std::cout << "vertex shader compilation failed" << std::endl;
		else if (shaderType == GL_FRAGMENT_SHADER)
			std::cout << "fragment shader compilation failed" << std::endl;
		PrintShaderLog(numCompiled);
		return 0;
	}
	return shader;
}
