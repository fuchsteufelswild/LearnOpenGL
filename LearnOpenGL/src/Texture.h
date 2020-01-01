#pragma once

#include <string>

class Texture
{
private:
	unsigned int m_TextureID;
	int m_Height, m_Width, m_BPP;
	unsigned char* m_TextureData;
public:
	Texture(std::string filePath, int p_Height = 0, int p_Width = 0, int p_BPP = 0);
	~Texture();

	void Bind(unsigned int textureUnit = 0) const;
	void Unbind() const;
};