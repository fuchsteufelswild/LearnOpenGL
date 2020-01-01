#pragma once

#include <glm\glm.hpp>

class Texture;

class ProjectiveSpotlight
{
private:
	glm::vec3 m_Pos;
	glm::vec3 m_Front; // The direction spotlight points
	glm::vec3 m_Right; // S coordinate
	glm::vec3 m_Up;    // T coordinate
	
	float     m_Angle; // Angle of the spotlight defines how wide it emits the light
	float     m_FocalLength;
	int       m_Width;
	int       m_Height;
	float     aspectRatio;


	// Matrices that will be used to transform the vertices
	glm::mat4 SLS;     // Spot light space
	glm::mat4 PT;      // Projective transform
	// -- 

	Texture* m_PaintTexture;
public:
	ProjectiveSpotlight(glm::vec3 p_Pos, glm::vec3 p_Front, float p_Angle, Texture* p_Texture, int p_Width = 512, int p_Height = 512);
	~ProjectiveSpotlight() = default;

	inline glm::mat4& GetViewMatrix() { return SLS; }
	inline glm::mat4& GetProjectiveTransformMatrix() { return PT; }

};