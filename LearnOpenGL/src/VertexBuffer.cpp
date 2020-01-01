#include "VertexBuffer.h"
#include "Renderer.h"
#include <GL\glew.h>
#include "Renderer.h"

#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCALL(glGenBuffers(1, &m_BufferID));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

	std::cout << "Vertex Buffer Created with id: " << m_BufferID << "\n";
}

VertexBuffer::~VertexBuffer()
{
	std::cout << "Vertex Buffer Deleted with id: " << m_BufferID << "\n";
	GLCALL(glDeleteBuffers(1, &m_BufferID));

	
}

void VertexBuffer::Bind() const 
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
}

void VertexBuffer::Unbind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}