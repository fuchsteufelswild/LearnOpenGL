#include "IndexBuffer.h"
#include "Renderer.h"

#include <iostream>

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
	: m_Count(count)
{
	ASSERT(sizeof(GLuint) == sizeof(unsigned int));

	GLCALL(glGenBuffers(1, &m_BufferID));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW));

	std::cout << "Index Buffer Created with id: " << m_BufferID << "\n";
}

IndexBuffer::~IndexBuffer()
{
	std::cout << "Index Buffer Deleted with id: " << m_BufferID << "\n";
	GLCALL(glDeleteBuffers(1, &m_BufferID));

	
}

void IndexBuffer::Bind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
}

void IndexBuffer::Unbind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}