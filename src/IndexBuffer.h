#pragma once

class IndexBuffer
{
private:
	unsigned int indexBufferID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int m_Count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; };
};
