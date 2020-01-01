//#pragma once
//
//#include <string>
//#include <unordered_map>
//
//#include <gl\glew.h>
//
//#include <glm\glm.hpp>
//#include <glm\gtc\type_ptr.hpp>
//
//
//// Stores source file for all sub-shader types
//struct ShaderProgramSource
//{
//	std::string vertexShader;
//	std::string fragmentShader;
//};
//
//class Shader
//{
//private:
//	unsigned int m_ShaderID;
//	std::unordered_map< std::string, int> m_CacheUniformVariable; // Cache to store locations of uniforms
//public:
//	Shader(const std::string& filePath);
//	~Shader();
//	
//	void Bind() const;
//	void Unbind() const;
//	
//	// --- Uniform setters ---
//	template<typename T>
//	void SetUniform(const std::string& uniformName, T& data) { static_assert(false); }
//	
//	template<>
//	void SetUniform<float>(const std::string& uniformName, float& data) 
//	{ glUniform1fv(GetUniformLocation(uniformName), 1, &data); }
//	
//	template<>
//	void SetUniform<unsigned int>(const std::string& uniformName, unsigned int& data) 
//	{ glUniform1uiv(GetUniformLocation(uniformName), 1, &data); }
//	
//	template<>
//	void SetUniform<glm::vec4>(const std::string& uniformName, glm::vec4& data) 
//	{ glUniform4fv(GetUniformLocation(uniformName), 4, glm::value_ptr(data)); }
//	
//	template<>
//	void SetUniform<glm::mat4>(const std::string& uniformName, glm::mat4& data) 
//	{ glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(data)); }
//	// ----------------------
//
//	int GetUniformLocation(const std::string& uniformName);
//private:
//	// --- Shader Initializaiton ---
//	ShaderProgramSource ParseShaderFile(const std::string& filePath);
//	unsigned int CompileShader(unsigned int type, const std::string& shaderSource);
//	unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
//	// -----------------------------
//};