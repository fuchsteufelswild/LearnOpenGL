#pragma once

#include <glm\glm.hpp>

class Material;
class Mesh;

class Light
{
protected:
	glm::vec4 m_Position;
	glm::vec4 m_LightColor;
	unsigned int m_Intensity;
	unsigned int id;
public:
	Light(glm::vec4 p_Position, glm::vec4 p_LightColor, unsigned int p_Intensity);
	virtual ~Light() = default;

	virtual void SetUniforms(Material* material) = 0;

public:
	void SetLightPosition(glm::vec4 newPos);
	void SetLightColor(glm::vec4 newColor);
	void SetLightIntensity(unsigned int newIntensity);
	virtual void SetExponent(float exponent);
public:
	glm::vec4 GetLightPosition() const;
	glm::vec4 GetLightColor() const;
	unsigned int GetLightIntensity() const;
};

class AmbientLight : public Light
{
public:
	static unsigned int count;
public:
	AmbientLight(glm::vec4 p_Position, glm::vec4 p_LightColor, unsigned int p_Intensity)
		: Light(p_Position, p_LightColor, p_Intensity) { id = AmbientLight::count++; }

	virtual void SetUniforms(Material* material) override;
};


class PointLight : public Light
{
private:
	float c_AttenuationConstant; // constant  
	float l_AttenuationConstant; // linear
	float q_AttenuationConstant; // quadratic
public:
	static unsigned int count;
public:
	PointLight(glm::vec4 p_Position, glm::vec4 p_LightColor, unsigned int p_Intensity,
			   float pc_AttenuationConstant = 1, float pl_AttenuationConstant = 1, float pq_AttenuationConstant = 1)
		: Light(p_Position, p_LightColor, p_Intensity),
		  c_AttenuationConstant(pc_AttenuationConstant), l_AttenuationConstant(pl_AttenuationConstant), q_AttenuationConstant(pq_AttenuationConstant) { id = PointLight::count++; }

	virtual void SetUniforms(Material* material) override;
};



class SpotLight : public Light
{
private:
	float c_AttenuationConstant; // constant  
	float l_AttenuationConstant; // linear
	float q_AttenuationConstant; // quadratic
	unsigned int spotLightExponent;
	glm::vec4 m_Direction;

public:
	static unsigned int count;
public:
	SpotLight(glm::vec4 p_Position, glm::vec4 p_LightColor, unsigned int p_Intensity, glm::vec4 p_Direction,
		float pc_AttenuationConstant = 1, float pl_AttenuationConstant = 1, float pq_AttenuationConstant = 1)
		: Light(p_Position, p_LightColor, p_Intensity), m_Direction(p_Direction),
		c_AttenuationConstant(pc_AttenuationConstant), l_AttenuationConstant(pl_AttenuationConstant), q_AttenuationConstant(pq_AttenuationConstant) { id = SpotLight::count++; }

	virtual void SetUniforms(Material* material) override;
	virtual void SetExponent(float exponent) override;
};


class DirectionalLight : public Light
{
private:
	glm::vec4 m_Direction;
public:
	static unsigned int count;
public:
	DirectionalLight(glm::vec4 p_Position, glm::vec4 p_LightColor, unsigned int p_Intensity,
					 glm::vec4 p_Direction)
		: Light(p_Position, p_LightColor, p_Intensity), m_Direction(p_Direction) { id = DirectionalLight::count++; }

	virtual void SetUniforms(Material* material) override;
};






