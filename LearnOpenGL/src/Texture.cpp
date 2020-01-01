#include "Texture.h"
#include "Renderer.h"

#include <GL\glew.h>

#include <stb_image\stb_image.h>

Texture::Texture(std::string filePath, int p_Height, int p_Width, int p_BPP)
	:	m_Height(p_Height), m_Width(p_Width), m_BPP(p_BPP), m_TextureData(nullptr)
{
	stbi_set_flip_vertically_on_load(1);

	const char* src = filePath.c_str();
	m_TextureData = stbi_load(src, &m_Width, &m_Height, &m_BPP, 0);

	GLCALL(glGenTextures(1, &m_TextureID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TextureData));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

	

	
	// GLCALL(glGenerateMipmap(GL_TEXTURE_2D));

	// Clear memory ( optional )
//	stbi_image_free(m_TextureData);

	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
	GLCALL(glDeleteTextures(1, &m_TextureID));
}

void Texture::Bind(unsigned int textureUnit) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + textureUnit));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void Texture::Unbind() const
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}