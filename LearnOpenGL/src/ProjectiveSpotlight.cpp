#include "ProjectiveSpotlight.h"
#include <iostream>
#include "Utils.hpp"

using namespace Utils;

ProjectiveSpotlight::ProjectiveSpotlight(glm::vec3 p_Pos, glm::vec3 p_Front, float p_Angle, Texture* p_Texture, int p_Width, int p_Height)
	: m_Pos(p_Pos), m_Front(p_Front), m_Angle(p_Angle), m_PaintTexture(p_Texture), m_Width(p_Width), m_Height(p_Height)
{
	aspectRatio = m_Height / m_Width;

	m_Right = glm::vec3(m_Front.z, m_Front.y, -m_Front.x);
	m_Up = glm::cross(m_Front, m_Right);

	m_FocalLength = 1.0f / (glm::tan(glm::radians(m_Angle / 2.0f)));


	m_FocalLength = 1.0f / (glm::tan(glm::radians(m_Angle / 2.0f)));
	SLS = glm::mat4(1.0f);
	SLS[0] = glm::vec4(m_Right, -1 * glm::dot(m_Right, m_Pos));
	SLS[1] = glm::vec4(m_Up, -1 * glm::dot(m_Up, m_Pos));
	SLS[2] = glm::vec4(m_Front, -1 * glm::dot(m_Front, m_Pos));
	SLS[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	PT = glm::mat4(1);
	PT[0] = glm::vec4(m_FocalLength / 2, 0.0f, 0.5f, 0.0f);
	PT[1] = glm::vec4(0.0f, m_FocalLength / (2 * aspectRatio), 0.5f, 0.0f);
	PT[2] = glm::vec4(0.0f);
	PT[3] = glm::vec4(0, 0, 1, 0);

}