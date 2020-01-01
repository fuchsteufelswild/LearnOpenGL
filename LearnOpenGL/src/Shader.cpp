//#include "Shader.h"
//#include "Renderer.h"
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//
//#include <glm\gtc\type_ptr.hpp>
//
//Shader::Shader(const std::string& filePath)
//{
//	ShaderProgramSource shaderSources = ParseShaderFile("res/BasicShader.shader");
//	m_ShaderID = CreateShaderProgram(shaderSources.vertexShader, shaderSources.fragmentShader);
//}
//
//Shader::~Shader()
//{
//	glDeleteProgram(m_ShaderID);
//}
//
//// Given file contains all shader code parses 
//// and returns seperate shader files
//ShaderProgramSource Shader::ParseShaderFile(const std::string& filePath)
//{
//	std::ifstream file(filePath);
//	std::stringstream ss[2];
//
//	enum class ShaderType
//	{
//		NONE = -1, VERTEX = 0, FRAGMENT = 1
//	};
//
//	ShaderType type = ShaderType::NONE;
//
//	std::string line;
//	while (std::getline(file, line))
//	{
//		if (line.find("#shader") != std::string::npos)
//		{
//			if (line.find("vertex") != std::string::npos)
//				type = ShaderType::VERTEX;
//			else if (line.find("fragment") != std::string::npos)
//				type = ShaderType::FRAGMENT;
//		}
//		else
//			ss[static_cast<int>(type)] << line << "\n";
//	}
//
//	return { ss[0].str(), ss[1].str() };
//}
//
//// Compile the shader with given type and source file
//unsigned int Shader::CompileShader(unsigned int type, const std::string& shaderSource)
//{
//	unsigned int id = glCreateShader(type); // Get a shader id for a type
//	const char* source = shaderSource.c_str(); // Convert source to type of const char*
//	glShaderSource(id, 1, &source, nullptr); // Attain source file to the shader
//	
//	// Compile and check the status 
//	glCompileShader(id); // Compile Shader
//	int result;
//	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//	if (result == GL_FALSE)
//	{
//		int length;
//		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//		char *errMessage = (char*)alloca(length * sizeof(char)); 
//		glGetShaderInfoLog(id, length, &length, errMessage);
//
//		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!\n";
//		std::cout << errMessage << "\n";
//		glDeleteShader(id);
//		return 0;
//	}
//	// -- 
//
//	return id;
//}
//
//// Create a program and attach shaders to it
//unsigned int Shader::CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
//{
//	unsigned int program = glCreateProgram(); // Get ID for a program
//
//	// Compile shaders
//	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
//	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
//	// -- 
//
//	// Attach shaders to the program
//	GLCALL(glAttachShader(program, vs));
//	GLCALL(glAttachShader(program, fs));
//	// --
//
//	int result;
//	// Link and check status
//	GLCALL(glLinkProgram(program));
//	glGetProgramiv(program, GL_LINK_STATUS, &result);
//	if (result == GL_FALSE)
//	{
//		int length;
//		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
//		char *errMessage = (char*)alloca(length * sizeof(char));
//		glGetProgramInfoLog(program, length, &length, errMessage);
//		std::cout << "Error linking program: " << errMessage << "\n";
//	}
//	// --
//	// Validate and check status
//	GLCALL(glValidateProgram(program));
//	glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
//	if (result == GL_FALSE)
//	{
//		int length;
//		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
//		char *errMessage = (char*)alloca(length * sizeof(char));
//		glGetProgramInfoLog(program, length, &length, errMessage);
//		std::cout << "Error validating program: " << errMessage << "\n";
//	}
//	// --
//
//	// Delete shaders
//	GLCALL(glDeleteShader(vs));
//	GLCALL(glDeleteShader(fs));
//	// --
//
//	return program;
//}
//
////void Shader::SetUniform4f(const std::string& uniformName, float v1, float v2, float v3, float v4)
////{
////	int loc = GetUniformLocation(uniformName);
////	glUniform4f(loc, v1, v2, v3, v4);
////}
////
////void Shader::SetUniformMat4(const std::string& uniformName, glm::mat4 m)
////{
////	int location = GetUniformLocation(uniformName);
////
////	// glUniformMatrix4dv(location, 1, GL_FALSE, glm::value_ptr(m));
////	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m));
////}
//
//// Returns uniform's location
//int Shader::GetUniformLocation(const std::string& uniformName)
//{
//	// Check if already cached
//	if (m_CacheUniformVariable.find(uniformName) != m_CacheUniformVariable.end())
//		return m_CacheUniformVariable[uniformName];
//
//	const char* src = uniformName.c_str(); 
//	int loc = glGetUniformLocation(m_ShaderID, uniformName.c_str()); // Get location
//	if (loc == -1) // -1 -> uniform is not used or does not exist at all
//		std::cout << "Shader may not be used!\n";
//
//	m_CacheUniformVariable[uniformName] = loc; // Cache the uniform
//	return loc;
//}
//
//void Shader::Bind() const { GLCALL(glUseProgram(m_ShaderID)); }
//void Shader::Unbind() const { GLCALL(glUseProgram(0)); }