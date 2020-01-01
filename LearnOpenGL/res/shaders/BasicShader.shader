#shader vertex
#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 normals;
layout(location = 2) in vec2 text;

out vec4 vertexColor;
out vec4 normalCoord;
out vec4 position;
out vec2 texCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * pos;
	/*for (int i = 0; i < 2; ++i)
	{
		float dis = distance(u_PointLights[i].lightPosition, pos);
		float multiplier = 1 / (1 + dis + dis * dis);
		vec4 rColor = u_PointLights[i].lightColor * multiplier;
		
		vec4 dir = u_PointLights[i].lightPosition - pos;
		finalColor += rColor * (dot(dir, normals));
	}*/
	vertexColor = clamp(pos, 0.0f, 1.0f);
	//normalCoord = normalize(mat4(transpose(inverse(u_Model))) * normalize(normals));
	// gl_Position = u_View * u_Model * pos;
	
	position = u_Model * pos;
	normalCoord = normals;
	texCoord = text;
}

#shader fragment
#version 330 core

struct PointLight
{
	vec4 lightPosition;
	vec4 lightColor;
};
struct SpotLight
{
	vec4 lightPosition;
	vec4 lightColor;
	vec4 lightDirection;
	uint spotLightExponent;
};
struct DirectionalLight
{
	vec4 lightColor;
	vec4 lightDirection;
};
struct Material
{
	uint specularExponent;
	vec4 diffuseReflectionColor; // D
	vec4 specularReflectionColor; // S
};
struct Light
{
	vec4 diffuseLight;
	vec4 specularLight;
};

Light CalculateLight(vec4, vec4, int, int);

uniform Material mat;

uniform PointLight u_PointLights[1];
uniform SpotLight u_SpotLights[3];
// uniform PointLight u_DirectionalLights;

uniform float lightIntensity = 10.0f;

uniform float uc_AttenuationConstant = 1.0f;
uniform float ul_AttenuationConstant = 1.0f;
uniform float uq_AttenuationConstant = 1.0f;

uniform vec4 u_Color;
layout(location = 0) out vec4 color;

uniform sampler2D textureSampler;

in vec4 vertexColor;
in vec4 normalCoord;
in vec4 position;
in vec2 texCoord;

uniform vec4 u_AmbientColor;

uniform vec4 camPosition;

uniform float u_Result;

vec4 resss = vec4(0.0f, 0.0f, 0.0f, 0.0f);

Light CalculateLight(vec4 lPos, vec4 lColor, int type, int index)
{
	vec4 lightDir = normalize(lPos - position); 
	vec4 viewerDir = normalize(camPosition - position);  
	vec4 halfwayVec = normalize(lightDir + viewerDir);  

	float dotNormalLight = dot(lightDir, normalCoord); // Correlation between surface and the light

	// Calculate diminished light color 
	float dis = distance(lPos, position); 
	float multiplier = 1 / (uc_AttenuationConstant + ul_AttenuationConstant * dis + uq_AttenuationConstant * dis * dis);
	vec4 resultingLight = multiplier * lColor * lightIntensity;
	
	// If spot light
	if (type == 1) 
		resultingLight = resultingLight * pow(max(0, dot(lightDir, -u_SpotLights[index].lightDirection)), u_SpotLights[index].spotLightExponent) * 3;
	
	vec4 resultSpec = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	if (dotNormalLight >= 0) // If lightdir and surface normal are on the same side
		resultSpec = resultingLight * pow(max(0, dot(halfwayVec, normalCoord)), mat.specularExponent);

	return Light(resultingLight * max(0, dotNormalLight), resultSpec);
}

void main()
{
	vec4 finalTexture = texture(textureSampler, texCoord);
	Light rLight;
	vec4 resultingDiffuse = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vec4 resultingSpecular = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	// Point Lights
	for (int i = 0; i < u_PointLights.length(); ++i)
	{
		rLight = CalculateLight(u_PointLights[i].lightPosition, u_PointLights[i].lightColor, 0, i);

		resultingDiffuse += rLight.diffuseLight;
		resultingSpecular += rLight.specularLight;
	}
	// Spot Lights
	for (int i = 0; i < u_SpotLights.length(); ++i)
	{
		rLight = CalculateLight(u_SpotLights[i].lightPosition, u_SpotLights[i].lightColor, 1, i);
		resss = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		resultingDiffuse += rLight.diffuseLight;
		resultingSpecular += rLight.specularLight;
	}
	color = finalTexture * mat.diffuseReflectionColor * (u_AmbientColor + resultingDiffuse) + (mat.specularReflectionColor * resultingSpecular);
}