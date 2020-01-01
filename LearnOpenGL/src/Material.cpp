#include "Material.h"
#include "Renderer.h"
#include "Texture.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glm\gtc\type_ptr.hpp>

Material::Material(const std::string& filePath, unsigned int p_SpecularExponent, Texture* p_Texture, glm::vec4 SRC, glm::vec4 DRC)
	:	m_SpecularExponent(p_SpecularExponent), m_SpecularReflectionColor(SRC), m_DiffuseReflectionColor(DRC), m_Texture(p_Texture)
{
	ShaderProgramSource shaderSources = ParseShaderFile(filePath);
	m_MaterialID = CreateShaderProgram(shaderSources.vertexShader, shaderSources.fragmentShader);
}

Material::~Material()
{
	glDeleteProgram(m_MaterialID);
}

// Given file contains all shader code parses 
// and returns seperate shader files
ShaderProgramSource Material::ParseShaderFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	std::stringstream ss[2];

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	ShaderType type = ShaderType::NONE;

	std::string line;
	while (std::getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
			ss[static_cast<int>(type)] << line << "\n";
	}

	return { ss[0].str(), ss[1].str() };
}

// Compile the shader with given type and source file
unsigned int Material::CompileShader(unsigned int type, const std::string& shaderSource)
{
	unsigned int id = glCreateShader(type); // Get a shader id for a type
	const char* source = shaderSource.c_str(); // Convert source to type of const char*
	glShaderSource(id, 1, &source, nullptr); // Attain source file to the shader

	// Compile and check the status 
	glCompileShader(id); // Compile Shader
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *errMessage = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, errMessage);

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!\n";
		std::cout << errMessage << "\n";
		glDeleteShader(id);
		return 0;
	}
	// -- 

	return id;
}

// Create a program and attach shaders to it
unsigned int Material::CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	unsigned int program = glCreateProgram(); // Get ID for a program

	// Compile shaders
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	// -- 

	// Attach shaders to the program
	GLCALL(glAttachShader(program, vs));
	GLCALL(glAttachShader(program, fs));
	// --

	int result;
	// Link and check status
	GLCALL(glLinkProgram(program));
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char *errMessage = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, errMessage);
		std::cout << "Error linking program: " << errMessage << "\n";
	}
	// --

	// Validate and check status
	GLCALL(glValidateProgram(program));
	glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char *errMessage = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, errMessage);
		std::cout << "Error validating program: " << errMessage << "\n";
	}
	// --

	// Delete shaders
	GLCALL(glDeleteShader(vs));
	GLCALL(glDeleteShader(fs));
	// --

	return program;
}

// Returns uniform's location
int Material::GetUniformLocation(const std::string& uniformName)
{
	// Check if already cached
	if (m_CacheUniformVariable.find(uniformName) != m_CacheUniformVariable.end())
		return m_CacheUniformVariable[uniformName];

	const char* src = uniformName.c_str();
	int loc = glGetUniformLocation(m_MaterialID, uniformName.c_str()); // Get location
	if (loc == -1) // -1 -> uniform is not used or does not exist at all
		std::cout << "Shader may not be used!\n";

	m_CacheUniformVariable[uniformName] = loc; // Cache the uniform
	return loc;
}

glm::vec4& Material::GetSRC() { return m_SpecularReflectionColor; }
glm::vec4& Material::GetDRC() { return m_DiffuseReflectionColor; }

unsigned int& Material::GetSpecularExponent() { return m_SpecularExponent; }
Texture* Material::GetTexture() { return m_Texture; }

void Material::SetSpecularExponent(unsigned int newExponent) { m_SpecularExponent = newExponent; }
void Material::SetTexture(Texture* newTexture) { m_Texture = newTexture; }

void Material::Bind() const 
{ 
	GLCALL(glUseProgram(m_MaterialID)); 
	m_Texture->Bind();
}

void Material::Unbind() const 
{ 
	GLCALL(glUseProgram(0));
	m_Texture->Unbind();
}