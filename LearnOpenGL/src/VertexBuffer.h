#pragma once

class VertexBuffer 
{
private:
	unsigned int m_BufferID;
public:
	VertexBuffer() = delete;
	explicit VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};