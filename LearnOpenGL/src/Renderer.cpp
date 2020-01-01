#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Mesh.h"

// Utils
// Clear errors
void GlClearError() { while (glGetError()); }

// Check if there is any error 
bool GlCheckError(const char* function, const char* file, unsigned int line)
{
	if (glGetError())
	{
		std::cout << "Error executing function: " << function << " in file: \n" <<
			file << " on line: " << line;
		return false;
	}
	return true;
}
// -- 

Renderer::~Renderer()
{
	layouts.erase(layouts.begin(), layouts.end());
	layouts.clear();
}

// Main renderer tasks
void Renderer::ClearScreen() const { GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); }

void Renderer::Draw(Mesh& mesh)
{
	mesh.Bind();

	GLCALL(glDrawElements(GL_TRIANGLES, mesh.GetIBCount(), GL_UNSIGNED_INT, 0));

}
// -- 

VertexBufferLayout& Renderer::GetLayout(std::string layoutName)
{
	if (layouts.find(layoutName) != layouts.end())
		return layouts[layoutName];

	std::cout << "Layout: " << layoutName << " does not exist!\n";
	ASSERT(false);
}
