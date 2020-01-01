#pragma once

class IndexBuffer
{
private:
	unsigned int m_BufferID; // Assigned ID
	unsigned int m_Count; 
public:
	IndexBuffer() = delete;
	explicit IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};