@startuml
class Renderer {
    + void Clear() const;
    + void Draw(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader) const;
}

class Shader {
    - std::string vShaderFilePath
    - std::string fShaderFilePath
    - unsigned int shaderID
    - std::unordered_map<std::string, int> m_UniformLocationCache
    + Shader(const std::string& vertexFile, const std::string& fragFile)
    ~Shader()
    + void Bind() const
    + void Unbind() const
    + void SetUniform1i(const std::string& name, float value)
    + void SetUniform1f(const std::string& name, float value)
    + void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
    + void SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
    - std::string readShaderSource(const std::string& filePath)
    - unsigned int CreateShader(const std::string& vShaderSrc, const std::string& fShaderSrc)
    - unsigned int CompileShader(unsigned int shaderType, const std::string& shaderSrc)
    - int GetUniformLocation(const std::string& name)
}

class VertexArray {
    - unsigned int vertexArrayID
    + VertexArray()
    ~VertexArray()
    + void Bind() const
    + void Unbind() const
    + void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
}

class VertexBuffer {
    - unsigned int vertexBufferID
    + VertexBuffer(const void* data, unsigned int size)
    + void Bind() const
    + void Unbind() const
    ~VertexBuffer()
}

class IndexBuffer {
    - unsigned int indexBufferID
    - unsigned int m_Count
    + IndexBuffer(const unsigned int* data, unsigned int m_Count)
    + unsigned int GetCount() const
    + void Bind() const
    + void Unbind() const
    ~IndexBuffer()
}

class VertexBufferLayout {
    - std::vector<VertexBufferElement> m_Elements
    - unsigned int m_Stride
    + VertexBufferLayout()
    + void Push<T>(unsigned int count)
    + void Push<float>(unsigned int count)
    + void Push<unsigned int>(unsigned int count)
    + void Push<unsigned char>(unsigned int count)
    + const std::vector<VertexBufferElement> GetElements() const
    + unsigned int GetStride() const
}

class VertexBufferElement {
    + unsigned int type
    + unsigned int count
    + unsigned char normalized

    + static unsigned int GetSizeOfType(unsigned int type)
}

class Texture {
    - unsigned int m_RendererID
    - unsigned char* m_LocalBuffer
    - int m_Width
    - int m_Height
    - int m_BPP
    + Texture(const std::string& path)
    + void Bind(unsigned int slot = 0) const
    + void UnBind() const
    + int GetWidth() const
    + int GetHeight() const
    ~Texture()
}

VertexArray --> VertexBuffer : "uses"
VertexArray --> VertexBufferLayout : "uses"
Renderer --> Shader : "uses"
Renderer --> VertexArray : "uses"
Renderer --> IndexBuffer : "uses"
Texture --> Shader : "uses"
VertexBufferLayout *-- "1..*" VertexBufferElement : "contains"
@enduml
