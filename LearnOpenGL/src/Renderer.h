#pragma once

#include <GL\glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
// #include "Shader.h"
#include "VertexBufferLayout.h"

#include <unordered_map>
#include <iostream>
#include <string>

class Mesh;

#define ASSERT(x) if(!(x)) __debugbreak();

// Wrapper for opengl functions to check for errors 
#define GLCALL(x) GlClearError();\
x;\
ASSERT(GlCheckError(#x, __FILE__, __LINE__));

// GlErrorChecking Calls
void GlClearError();
bool GlCheckError(const char* function, const char* file, unsigned int line);

// Singleton Renderer class implemented with LazyInitialization
// Only one renderer is expected to exist in the scene for now
// Draws given VA with assigned shaders
class Renderer
{
public:
	static Renderer& GetInstance()
	{
		static Renderer rendererInstance;

		return rendererInstance;
	}

	Renderer(const Renderer& rRenderer) = delete;
	void operator=(const Renderer& rRenderer) = delete;

	~Renderer();

	void ClearScreen() const;
	// void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	// void Draw(const Mesh& mesh, const Shader& shader) const;
	void Draw(Mesh& mesh);

	VertexBufferLayout& GetLayout(std::string layoutName);
	inline void AddLayout(std::string layoutName, VertexBufferLayout& layout) { layouts[layoutName] = layout; }
private:
	Renderer() = default;
	std::unordered_map<std::string, VertexBufferLayout> layouts; // Cache layouts in case of future use
};