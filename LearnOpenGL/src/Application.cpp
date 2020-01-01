#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Window.h"
// Vertex Array, Index Buffer, and Shader headers already exist in Rendrer.h
// VertexArray.h includes VertexBuffer.h
#include "Renderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Light.h"

#include "VertexBufferLayout.h"
#include "Texture.h"

#include "ProjectiveSpotlight.h"
#include "Utils.hpp"

using namespace Utils;
//struct Vertex
//{
//	unsigned int id;
//	glm::vec3 position;
//	glm::vec3 normal;
//	glm::vec2 texture;
//};



const float toRadians = 3.14f / 180.0f;
int main(void)
{
	std::vector<Light*> lights;
	Camera cam;
	Window mainWindow(1920, 1080, "Hello", &cam);

	// Vertex attributes
	// Position,     Normal,     UV
	float positions[] = {
		-0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 0.0f,   0.0f, 0.0f, // index = 0
		 0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 0.0f,   1.0f, 0.0f,// 1
		 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 0.0f,   1.0f, 1.0f,// 2
		-0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 0.0f,   0.0f, 1.0f,// 3
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,// behind 0 ( 4 )
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,// behind 3 ( 5 )
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // behind 2 ( 6 )
		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f, // behind 1 ( 7 )
	    -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 0.0f,   0.0f, 0.0f, // index = 0
		 0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 0.0f,   0.0f, 1.0f, // 1
		 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 0.0f,   0.0f, 0.0f, // 2
		-0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 0.0f,   0.0f, 1.0f, // 3
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // behind 0 ( 4 )
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f, // behind 3 ( 5 )
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // behind 2 ( 6 )
		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f // behind 1 ( 7 )
	};

	// Index buffer indices
	unsigned int indices[] = {
		0, 1, 2, // Forward face
		0, 2, 3, // 
		4, 5, 7, // Rear face
		5, 6, 7, // 
		13, 11, 8, // Left face
		12, 13, 8, // 
		9, 10, 14, // Right face
		9, 14, 15, //
		2, 3, 6, // Top face
		3, 5, 6, //
		9, 12, 8, // Bottom face
		15, 12, 9  //
	};

	float triangleNormals[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	float vertexNormals[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	float positions1[] = {
		-0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 0.0f,	0.0f, 0.0f,  // index = 0
		 0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// 1
		 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// 2
		-0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 0.0f,	0.0f, 1.0f,	// 3
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// behind 0 ( 4 )
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// behind 3 ( 5 )
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// behind 2 ( 6 )
		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,	0.0f, 0.0f	// behind 1 ( 7 )
	};

	float positions2[] = {
		-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 0.0f,	0.0f, 0.0f,  // index = 0
		 0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// 1
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// 2
		-0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 0.0f,	0.0f, 1.0f,	// 3
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f, 	1.0f, 0.0f,	// behind 0 ( 4 )
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f, 	0.0f, 0.0f,	// behind 3 ( 5 )
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f, 	1.0f, 0.0f,	// behind 2 ( 6 )
		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,	 	0.0f, 0.0f	// behind 1 ( 7 )
	};

	// Index buffer indices
	unsigned int indices1[] = {
		1, 0, 2, // Forward face
		0, 3, 2, // 
		5, 4, 7, // Rear face
		6, 5, 7, // 
		3, 0, 4, // Left face
		3, 4, 5, // 
		1, 2, 7, // Right face
		2, 6, 7, //
		2, 3, 6, // Top face
		3, 5, 6, //
		7, 0, 1, // Bottom face
		7, 4, 0  //
	};

	// Index buffer indices
	unsigned int indices2[] = {
		1, 0, 2, // Forward face
		0, 3, 2, // 
		5, 4, 7, // Rear face
		6, 5, 7, // 
		3, 0, 4, // Left face
		3, 4, 5, // 
		1, 2, 7, // Right face
		2, 6, 7, //
		2, 3, 6, // Top face
		3, 5, 6, //
		7, 0, 1, // Bottom face
		7, 4, 0  //
	};

	float triangleNormals1[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	float vertexNormals1[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	Utils::CalculateTriangleNormals(positions, vertexNormals, triangleNormals, indices, 12, 16, 8);
	std::cout << " ------------------ \n";
	Utils::CalculateTriangleNormals(positions1, vertexNormals1, triangleNormals1, indices1, 12, 8, 6);
	

	for (int i = 0; i < 16; ++i)
	{
		positions[i * 8 + 3] = vertexNormals[i * 3 + 0];
		positions[i * 8 + 4] = vertexNormals[i * 3 + 1];
		positions[i * 8 + 5] = vertexNormals[i * 3 + 2];
	}

	for (int i = 0; i < 8; ++i)
	{
		positions1[i * 8 + 3] = vertexNormals1[i * 3 + 0];
		positions1[i * 8 + 4] = vertexNormals1[i * 3 + 1];
		positions1[i * 8 + 5] = vertexNormals1[i * 3 + 2];
	}
	
	std::string brickPath = "res/textures/brick.png";
	std::string dirtPath = "res/textures/dirt.png";
	std::string plainPath = "res/textures/plain.png";
	std::string birdPath = "res/textures/Icon_Bird_512x512.png";

	Texture brickTexture(brickPath);
	Texture dirtTexture(dirtPath);
	Texture plainTexture(plainPath);
	Texture birdTexture(birdPath);

	/*
	GLCALL(glEnable(GL_BLEND));
	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));*/
	Material material2("res/shaders/ProjectiveShader.shader", 2, &birdTexture);
	material2.Unbind();

	Material material("res/shaders/BasicShader.shader", 2, &brickTexture);
	material.SetTexture(&brickTexture);
	material.Unbind();
	Material material1("res/shaders/BasicShader.shader", 5, &plainTexture, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.7f, 0.6f, 0.4f, 1.0f));
	material1.Unbind();


	glm::vec4 ambientColor = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	float diffuseConstant = 1.0f;
	

	VertexBufferLayout vbLayout;
	vbLayout.Push<float>(3);
	vbLayout.Push<float>(3);
	vbLayout.Push<float>(2);
	Renderer::GetInstance().AddLayout("3_3_2", vbLayout);

	VertexBufferLayout pLayout;
	pLayout.Push<float>(3);
	pLayout.Push<float>(3);
	Renderer::GetInstance().AddLayout("3_3", pLayout);

	
	float testPositions[] = {
		1.0f, 11.2f, -7.0f,     0.0f, 0.0f, 0.0f,
		1.0f, 9.2f, -7.0f,   0.0f, 0.0f, 0.0f,
	   -1.0f,  11.2f, -7.0f,  0.0f, 0.0f, 0.0f,
		-1.0f,  9.2f, -7.0f,	  0.0f, 0.0f, 0.0f
	};

	unsigned int testIndices[] = {
		1, 0, 2, // Forward face
		2, 3, 1
	};

	float testTriangleNormals[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	float testVertexNormals[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};
		
		
	Utils::CalculateTriangleNormals(testPositions, testVertexNormals, testTriangleNormals, testIndices, 2, 4, 6);
	for (int i = 0; i < 4; ++i)
	{
		testPositions[i * 6 + 3] = testVertexNormals[i * 3 + 0];
		testPositions[i * 6 + 4] = testVertexNormals[i * 3 + 1];
		testPositions[i * 6 + 5] = testVertexNormals[i * 3 + 2];
		// std::cout << testVertexNormals[i * 3 + 0] << " " << testVertexNormals[i * 3 + 1] << " " << testVertexNormals[i * 3 + 2] << "\n";
	}
	ProjectiveSpotlight psl(glm::vec3(0.0f, 10.2f, -6.0f), glm::vec3(0.0f, 0.0f, -1.0f), 90, &birdTexture); // Create a projective spotlight
	


	// Create meshes 
	Mesh mesh5(GL_FLOAT, testPositions, 4 * 6, testIndices, 6, "3_3");
	mesh5.SetMaterial(&material2);
	Mesh mesh1(GL_FLOAT, positions, 16 * 8, indices, 36, "3_3_2");
	Mesh mesh(GL_FLOAT, positions, 16 * 8, indices, 36, "3_3_2");
	
	mesh.SetMaterial(&material1);
	mesh1.SetMaterial(&material);

	Mesh mesh2(mesh);
	Mesh mesh3(mesh);
	
	
	// Point light rotation
	float radius = 4.0f;
	float angle = 270.0f;
	float incrad = 0.2f;
	glm::vec3 pos = glm::vec3(1.0f, 4.0f, 4.0f);
	glm::vec3 center = glm::vec3(pos.x - radius * cos(angle * toRadians), pos.y, pos.z - radius * -1 * sin(angle * toRadians));

	// Spotlight movement 
	// Start end pairs for two spotlight
	float spotfs = -8.0f;
	float spotfe = 10.0f;
	float spotss = 10.0f; 
	float spotse = -8.0f;

	float spotfp = -2.0f; 
	float spotsp = 4.0f; 

	float fchange = 0.01f;
	float schange = -0.01f;
	//

	unsigned int exp = 50;
	unsigned int timer = 0;
	bool dir = false;

	// Create a projection matrix
	glm::mat4 projectionMatrix = glm::perspective(45.0f, 480.0f / 640.0f, 0.1f, 100.0f);
	float dif = -0.001f;
	float r = 0.6f;
	float startingAngle = 0.0f;
	float incrementAngle = 0.01f;


	// Add lights
	lights.push_back(new PointLight(glm::vec4(1.0f, 4.0f, -9.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1));
	lights.push_back(new SpotLight(glm::vec4(spotfp, 3.5f, -2.75f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 1, glm::vec4(0.0f, -1.0f, 0.0f, 0.0f)));
	lights.push_back(new SpotLight(glm::vec4(spotsp, 3.5f, -2.75f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 1, glm::vec4(0.0f, -1.0f, 0.0f, 0.0f)));
	lights.push_back(new SpotLight(glm::vec4(0.0f, 10.2f, -6.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, .0f), 1, glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(mainWindow.GetWindow()))
	{
		glm::vec4 regulated = glm::vec4(mainWindow.GetMainCamera()->GetCameraPosition(), 1.0f);

		mesh1.GetMaterial()->Bind();
		mesh1.GetMaterial()->SetUniform<glm::vec4>("camPosition", regulated);
		mesh1.GetMaterial()->SetUniform<unsigned int>("u_SpecularExponent", exp);
		mesh1.GetMaterial()->SetUniform<float>("u_SpecularConstant", diffuseConstant);

		mesh.GetMaterial()->Bind();
		mesh.GetMaterial()->SetUniform<glm::vec4>("camPosition", regulated);
		mesh.GetMaterial()->SetUniform<unsigned int>("u_SpecularExponent", exp);
		mesh.GetMaterial()->SetUniform<float>("u_SpecularConstant", diffuseConstant);

		mesh5.GetMaterial()->Bind();
		mesh5.GetMaterial()->SetUniform<glm::vec4>("camPosition", regulated);
		mesh5.GetMaterial()->SetUniform<unsigned int>("u_SpecularExponent", exp);
		mesh5.GetMaterial()->SetUniform<float>("u_SpecularConstant", diffuseConstant);


		startingAngle += incrementAngle;
		if (startingAngle >= 360.0f)
			startingAngle = 0.0f;
		glm::mat4 modelMatrix;
		glm::mat4 viewMatrix = mainWindow.GetMainCamera()->GetViewMatrix();
		modelMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.5f, -2.5f));
		
		glm::vec4 color = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f);
		
		// Set essentials on each material
		mesh1.GetMaterial()->Bind();
		mesh1.GetMaterial()->SetUniform<glm::vec4>("u_AmbientColor", ambientColor);
		mesh1.GetMaterial()->SetUniform<float>("u_DiffuseConstant", diffuseConstant);

		mesh1.GetMaterial()->SetUniform<glm::vec4>("u_Color", color);
		mesh1.GetMaterial()->SetUniform<glm::mat4>("u_Model", modelMatrix);
		mesh1.GetMaterial()->SetUniform<glm::mat4>("u_Projection", projectionMatrix);
		mesh1.GetMaterial()->SetUniform<glm::mat4>("u_View", viewMatrix);

		mesh1.GetMaterial()->SetUniform<glm::vec4>("mat.diffuseReflectionColor", mesh1.GetMaterial()->GetDRC());
		mesh1.GetMaterial()->SetUniform<glm::vec4>("mat.specularReflectionColor", mesh1.GetMaterial()->GetSRC());
		mesh1.GetMaterial()->SetUniform<unsigned int>("mat.specularExponent", mesh1.GetMaterial()->GetSpecularExponent());

		mesh.GetMaterial()->Bind();
		mesh.GetMaterial()->SetUniform<glm::vec4>("u_AmbientColor", ambientColor);
		mesh.GetMaterial()->SetUniform<float>("u_DiffuseConstant", diffuseConstant);

		mesh.GetMaterial()->SetUniform<glm::vec4>("u_Color", color);
		mesh.GetMaterial()->SetUniform<glm::mat4>("u_Model", modelMatrix);
		mesh.GetMaterial()->SetUniform<glm::mat4>("u_Projection", projectionMatrix);
		mesh.GetMaterial()->SetUniform<glm::mat4>("u_View", viewMatrix);

		mesh.GetMaterial()->SetUniform<glm::vec4>("mat.diffuseReflectionColor", mesh.GetMaterial()->GetDRC());
		mesh.GetMaterial()->SetUniform<glm::vec4>("mat.specularReflectionColor", mesh.GetMaterial()->GetSRC());
		mesh.GetMaterial()->SetUniform<unsigned int>("mat.specularExponent", mesh.GetMaterial()->GetSpecularExponent());

		mesh5.GetMaterial()->Bind();
		mesh5.GetMaterial()->SetUniform<glm::vec4>("u_AmbientColor", ambientColor);
		mesh5.GetMaterial()->SetUniform<float>("u_DiffuseConstant", diffuseConstant);

		mesh5.GetMaterial()->SetUniform<glm::vec4>("u_Color", color);
		mesh5.GetMaterial()->SetUniform<glm::mat4>("u_Model", modelMatrix);
		mesh5.GetMaterial()->SetUniform<glm::mat4>("u_Projection", projectionMatrix);
		mesh5.GetMaterial()->SetUniform<glm::mat4>("u_View", viewMatrix);

		mesh5.GetMaterial()->SetUniform<glm::vec4>("mat.diffuseReflectionColor", mesh5.GetMaterial()->GetDRC());
		mesh5.GetMaterial()->SetUniform<glm::vec4>("mat.specularReflectionColor", mesh5.GetMaterial()->GetSRC());
		mesh5.GetMaterial()->SetUniform<unsigned int>("mat.specularExponent", mesh5.GetMaterial()->GetSpecularExponent());

		
		
		glm::vec4 pLight1(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 pos1(1.0f, 4.0f, -9.0f, 1.0f);

		angle += incrad;
		if (angle >= 360.0f)
			angle -= 360.0f;

		pos1.x = center.x + radius * cos(angle * toRadians);
		pos1.z = (center.z + radius * sin(angle * toRadians));

		glm::vec4 currentPos = lights[0]->GetLightPosition();

		lights[0]->SetLightPosition(glm::vec4(center.x + radius * cos(angle * toRadians), currentPos.y, center.z + radius * sin(angle * toRadians), currentPos.w));

		spotfp += fchange;
		spotsp += schange;

		if (spotfp >= spotfe + 0.2f || spotfp <= spotfs - 0.2f)
			fchange = -fchange;
		if (spotsp >= spotss + 0.2f || spotsp <= spotse - 0.2f)
			schange = -schange;

		r += dif;
		if (r <= -0.6f)
			dif = 0.001f;
		else if(r >= 0.6f)
			dif = -0.001f;

		// Update spotlights
		currentPos = lights[1]->GetLightPosition();
		lights[1]->SetLightPosition(glm::vec4(spotfp, currentPos.y, currentPos.z, currentPos.w));
		lights[1]->SetExponent(spotfp + 10);

		currentPos = lights[2]->GetLightPosition();
		lights[2]->SetLightPosition(glm::vec4(spotsp, currentPos.y, currentPos.z, currentPos.w));
		lights[2]->SetExponent(spotsp + 10);

		currentPos = lights[3]->GetLightPosition();
		lights[3]->SetLightPosition(glm::vec4(spotsp, currentPos.y, currentPos.z, currentPos.w));


		// Set Light uniforms in meshes
		for (Light* l : lights)
		{
			l->SetUniforms(mesh1.GetMaterial());
			l->SetUniforms(mesh.GetMaterial());
			l->SetUniforms(mesh5.GetMaterial());
		}
		Renderer::GetInstance().ClearScreen();

		// Projective Texturing implement on mesh5
		mesh5.GetMaterial()->Bind();
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
		mesh5.GetMaterial()->SetUniform<glm::mat4>("u_Model", modelMatrix);
		mesh5.GetMaterial()->SetUniform<glm::mat4>("u_Projection", projectionMatrix);
		mesh5.GetMaterial()->SetUniform<glm::mat4>("u_View", viewMatrix);
		mesh5.GetMaterial()->SetUniform<glm::mat4>("u_SpotProjection", psl.GetProjectiveTransformMatrix());
		mesh5.GetMaterial()->SetUniform<glm::mat4>("u_SpotView", psl.GetViewMatrix());
		Renderer::GetInstance().Draw(mesh5);

		// Object on the right
		mesh1.GetMaterial()->Bind();
		Renderer::GetInstance().Draw(mesh1);

		// Ground
		mesh3.GetMaterial()->Bind();
		modelMatrix = glm::translate(glm::mat4(1), glm::vec3(1.0f, -1.0f, 2.75f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(20.0f, 1.0f, 30.f));
		mesh3.GetMaterial()->SetUniform<glm::mat4>("u_Model", modelMatrix);
		Renderer::GetInstance().Draw(mesh3);
		
		// Little cube positioned at the center
		// the point light is rotating around

		mesh2.GetMaterial()->Bind();
		modelMatrix = glm::translate(glm::mat4(1), glm::vec3(pos1.x, pos1.y, pos1.z));
		modelMatrix = glm::translate(glm::mat4(1), glm::vec3(center.x, center.y, center.z));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
		mesh1.GetMaterial()->SetUniform<glm::mat4>("u_Model", modelMatrix);
		Renderer::GetInstance().Draw(mesh2);

		// Object on the left
		modelMatrix = glm::translate(glm::mat4(1), glm::vec3(2.0f, 0.5f, -2.5f));
		mesh.GetMaterial()->Bind();
		mesh.GetMaterial()->SetUniform<glm::mat4>("u_Model", modelMatrix);

		Renderer::GetInstance().Draw(mesh);

		mainWindow.Refresh(); // Clear buffers
	}

	
	glfwTerminate();
	return 0;
}