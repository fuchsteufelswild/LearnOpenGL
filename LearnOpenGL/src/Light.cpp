#include "Light.h"
#include "Material.h"
#include "Mesh.h"

#include <string>

unsigned int AmbientLight::count = 0;
unsigned int PointLight::count = 0;
unsigned int SpotLight::count = 0;
unsigned int DirectionalLight::count = 0;

Light::Light(glm::vec4 p_Position, glm::vec4 p_LightColor, unsigned int p_Intensity)
	:	m_Position(p_Position), m_LightColor(p_LightColor), m_Intensity(p_Intensity) { }

void Light::SetLightPosition(glm::vec4 newPos) { m_Position = newPos; }
void Light::SetLightColor(glm::vec4 newColor) { m_LightColor = newColor; }
void Light::SetLightIntensity(unsigned int newIntensity) { m_Intensity = newIntensity; }
void Light::SetExponent(float exponent) { }

glm::vec4 Light::GetLightPosition() const { return m_Position; }
glm::vec4 Light::GetLightColor() const { return m_LightColor; }
unsigned int Light::GetLightIntensity() const { return m_Intensity; }


// Ambient Light

void AmbientLight::SetUniforms(Material* material)
{
	// TODO
}


// Point Light

void PointLight::SetUniforms(Material* material)
{
	material->Bind();
	std::string nameBase = "u_PointLights[" + std::to_string(this->id) + "]"; // Base to refer lights in shader

	material->SetUniform<glm::vec4>(nameBase + ".lightPosition", this->m_Position);
	material->SetUniform<glm::vec4>(nameBase + ".lightColor", this->m_LightColor);

	material->SetUniform<float>("uc_AttenuationConstant", this->c_AttenuationConstant);
	material->SetUniform<float>("ul_AttenuationConstant", this->l_AttenuationConstant);
	material->SetUniform<float>("uq_AttenuationConstant", this->q_AttenuationConstant);
}

// Spot Light
void SpotLight::SetUniforms(Material* material)
{
	material->Bind();

	std::string nameBase = "u_SpotLights[" + std::to_string(this->id) + "]"; // Base to refer lights in shader
	material->SetUniform<glm::vec4>(nameBase + ".lightPosition", this->m_Position);
	material->SetUniform<glm::vec4>(nameBase + ".lightColor", this->m_LightColor);
	material->SetUniform<glm::vec4>(nameBase + ".lightDirection", this->m_Direction);
	material->SetUniform<unsigned int>(nameBase + ".spotLightExponent", this->spotLightExponent);

	material->SetUniform<float>("uc_AttenuationConstant", this->c_AttenuationConstant);
	material->SetUniform<float>("ul_AttenuationConstant", this->l_AttenuationConstant);
	material->SetUniform<float>("uq_AttenuationConstant", this->q_AttenuationConstant);
}

void SpotLight::SetExponent(float exponent) { this->spotLightExponent = exponent; }


// Directional Light
void DirectionalLight::SetUniforms(Material* material)
{
	material->Bind();

	std::string nameBase = "u_DirectionalLights[" + std::to_string(this->id) + "]"; // Base to refer lights in shader

	material->SetUniform<glm::vec4>(nameBase + ".lightDirection", this->m_Direction);
}





