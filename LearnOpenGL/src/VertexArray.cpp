#include "VertexArray.h"

#include <iostream>
#include <GL\glew.h>

#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCALL(glGenVertexArrays(1, &m_ArrayID));
	std::cout << "Vertex Array Created with id: " << m_ArrayID << "\n";
}

VertexArray::~VertexArray() 
{ 
	std::cout << "Vertex Array Deleted with id: " << m_ArrayID << "\n";
	GLCALL(glDeleteVertexArrays(1, &m_ArrayID));
}

void VertexArray::AssignBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	unsigned int offset = 0;
	const auto& elements = layout.GetElements();

	for (int i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));

		offset += element.count * Utils::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const 
{
	GLCALL(glBindVertexArray(m_ArrayID));
}

void VertexArray::Unbind() const 
{
	GLCALL(glBindVertexArray(0));
}
