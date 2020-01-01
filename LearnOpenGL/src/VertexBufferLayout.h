#pragma once

#include <GL\glew.h>

#include <vector>
#include "Utils.hpp"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int normalized;
	unsigned int count;
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> vertexBufferElements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) { }
	~VertexBufferLayout() = default;

	template<typename T>
	void Push(unsigned int count) { static_assert(false);  }

	template<>
	void Push<float>(unsigned int count)
	{
		vertexBufferElements.push_back({ GL_FLOAT, GL_FALSE, count });
		m_Stride += count * Utils::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		vertexBufferElements.push_back({ GL_UNSIGNED_INT, GL_FALSE, count });
		m_Stride += count * Utils::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<int>(unsigned int count)
	{
		vertexBufferElements.push_back({ GL_INT, GL_FALSE, count });
		m_Stride += count * Utils::GetSizeOfType(GL_INT);
	}

	template<> 
	void Push<unsigned char>(unsigned int count)
	{
		vertexBufferElements.push_back({ GL_UNSIGNED_INT, GL_TRUE, count });
		m_Stride += count * Utils::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	const std::vector<VertexBufferElement>& GetElements() const { return vertexBufferElements; }
	unsigned int GetStride() const { return m_Stride; }
};
