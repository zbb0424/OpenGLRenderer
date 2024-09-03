#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

class Shader
{
private:
	std::string vShaderFilePath;
	std::string fShaderFilePath;
	unsigned int shaderID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& vertexFile, const std::string& fragFile);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, float value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	std::string readShaderSource(const std::string& filePath);
	unsigned int CreateShader(const std::string& vShaderSrc, const std::string& fShaderSrc);
	unsigned int CompileShader(unsigned int shaderType, const std::string& shaderSrc);
	int GetUniformLocation(const std::string& name);
};
