#pragma once

#include <string>

class Shader
{
private:
	std::string vShaderFilePath;
	std::string fShaderFilePath;
	unsigned int shaderID;
public:
	Shader(const std::string& vertexFile, const std::string& fragFile);
	~Shader();

	void Bind() const;
	void Unbind() const;

private:
	std::string readShaderSource(const std::string& filePath);
	unsigned int CreateShader(const std::string& vShaderSrc, const std::string& fShaderSrc);
	unsigned int CompileShader(unsigned int shaderType, const std::string& shaderSrc);
};
