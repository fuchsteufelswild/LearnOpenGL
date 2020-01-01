#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

#include <gl\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

class Texture;
// Stores source file for all sub-shader types
struct ShaderProgramSource
{
	std::string vertexShader;
	std::string fragmentShader;
};

class Material
{
private:
	unsigned int m_MaterialID;
	std::unordered_map< std::string, int> m_CacheUniformVariable; // Cache to store locations of uniforms
	unsigned int m_SpecularExponent;
	glm::vec4 m_SpecularReflectionColor;
	glm::vec4 m_DiffuseReflectionColor;
	Texture* m_Texture;
public:
	Material(const std::string& filePath, unsigned int p_SpecularExponent = 50, Texture* p_Texture = nullptr,
			 glm::vec4 SRC = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4 DRC = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	~Material();

	void Bind() const;
	void Unbind() const;

	// --- Uniform getters ---
	template<typename T>
	void GetUniform(const std::string& uniformName, T* dest) { static_assert(false); }

	template<>
	void GetUniform<float>(const std::string& uniformName, float* dest)
	{
		float arr[1];
		glGetUniformfv(m_MaterialID, GetUniformLocation(uniformName), arr);
		//std::cout << arr[0] << "Float result!\n";
	}
	// ------------------------


	// --- Uniform setters ---
	template<typename T>
	void SetUniform(const std::string& uniformName, T& data) { static_assert(false); }

	template<>
	void SetUniform<float>(const std::string& uniformName, float& data)
	{
		glUniform1fv(GetUniformLocation(uniformName), 1, &data);
	}

	template<>
	void SetUniform<unsigned int>(const std::string& uniformName, unsigned int& data)
	{
		glUniform1uiv(GetUniformLocation(uniformName), 1, &data);
	}

	template<>
	void SetUniform<glm::vec4>(const std::string& uniformName, glm::vec4& data)
	{
		//glUniform4fv(GetUniformLocation(uniformName), 4, glm::value_ptr(data));
		glUniform4f(GetUniformLocation(uniformName), data.x, data.y, data.z, data.w);
	}

	template<>
	void SetUniform<glm::mat4>(const std::string& uniformName, glm::mat4& data)
	{
		glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(data));
	}
	// ----------------------

	int GetUniformLocation(const std::string& uniformName);

	glm::vec4& GetSRC();
	glm::vec4& GetDRC();
	unsigned int& GetSpecularExponent();
	Texture* GetTexture();

	void SetSpecularExponent(unsigned int newExponent);
	void SetTexture(Texture* newTexture);
private:
	// --- Shader Initializaiton ---
	ShaderProgramSource ParseShaderFile(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& shaderSource);
	unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	// -----------------------------
};