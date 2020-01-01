#pragma once

#include <gl\glew.h>
#include <glm\glm.hpp>
#include <iostream>
#include <vector>

namespace Utils
{ 
	// Get size of given GL type
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (static_cast<GLenum>(type))
		{
			case GL_FLOAT:		   return 4;
			case GL_UNSIGNED_INT:  return 4;
			case GL_INT:		   return 4;
			case GL_UNSIGNED_BYTE: return 1;
			case GL_BYTE:		   return 1;
			default: std::cout << "Error\n";
		}
		return 0;
	}

	template<typename T>
	static T Clamp(T targetValue, T minLimit, T maxLimit)
	{
		if (targetValue < minLimit)
			targetValue = minLimit;
		else if (targetValue > maxLimit)
			targetValue = maxLimit;

		return targetValue;
	}

	static std::ostream& operator<<(std::ostream& out, const glm::vec3& vec)
	{
		out << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]\n";
		return out;
	}

	static std::ostream& operator<<(std::ostream& out, const glm::vec4& vec)
	{
		out << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]\n";
		return out;
	}

	static std::ostream& operator<<(std::ostream& out, const glm::mat4& mat)
	{
		out << mat[0] << mat[1] << mat[2] << mat[3];
		return out;
	}

	// Fills given vertex normals array with normals of the vertices
	static void CalculateTriangleNormals(float* positions, float* vertexNormals, float* normals, unsigned int* indices, unsigned int triangleCount, unsigned int vertexCount, unsigned int numberOfUnitsInStride)
	{
		std::vector<std::vector<int> > vertexTriangles(vertexCount);

		for (unsigned int i = 0; i < triangleCount; ++i)
		{
			// Get Vertex IDs
			unsigned int p0ID = indices[i * 3 + 0];
			unsigned int p1ID = indices[i * 3 + 1];
			unsigned int p2ID = indices[i * 3 + 2];

			// Store which triangle contains the vertices
			vertexTriangles[p0ID].push_back(i);
			vertexTriangles[p1ID].push_back(i);
			vertexTriangles[p2ID].push_back(i);

			// Get corresponding vertex positions
			glm::vec3 p0(positions[p0ID * numberOfUnitsInStride + 0], positions[p0ID * numberOfUnitsInStride + 1], positions[p0ID * numberOfUnitsInStride + 2]);
			glm::vec3 p1(positions[p1ID * numberOfUnitsInStride + 0], positions[p1ID * numberOfUnitsInStride + 1], positions[p1ID * numberOfUnitsInStride + 2]);
			glm::vec3 p2(positions[p2ID * numberOfUnitsInStride + 0], positions[p2ID * numberOfUnitsInStride + 1], positions[p2ID * numberOfUnitsInStride + 2]);

			// Calculate the normal of the plane ( which triangle resides on )
			glm::vec3 result = glm::normalize(glm::cross(p2 - p0, p1 - p0));

			
			// std::cout << p0 << p1 << p2;

			// Assign normal values to result
			normals[i * 3 + 0] = result.x;
			normals[i * 3 + 1] = result.y;
			normals[i * 3 + 2] = result.z;
		}
		

		/*for (int i = 0; i < vertexTriangles.size(); ++i)
		{
			for (int j = 0; j < vertexTriangles[i].size(); ++j)
				std::cout << vertexTriangles[i][j] << " ";
			std::cout << "\n";
		}*/
		// Calculate vertex normals
		for (unsigned int i = 0; i < vertexCount; ++i)
		{
			// Sum of all triangles that share the vertex
			for (unsigned int j = 0; j < vertexTriangles[i].size(); ++j)
			{
				vertexNormals[i * 3 + 0] += normals[vertexTriangles[i][j] * 3 + 0];
				vertexNormals[i * 3 + 1] += normals[vertexTriangles[i][j] * 3 + 1];
				vertexNormals[i * 3 + 2] += normals[vertexTriangles[i][j] * 3 + 2];
			}
			
			// Average them
			vertexNormals[i * 3 + 0] /= vertexTriangles[i].size();
			vertexNormals[i * 3 + 1] /= vertexTriangles[i].size();
			vertexNormals[i * 3 + 2] /= vertexTriangles[i].size();
		}

		for (unsigned int i = 0; i < vertexCount; ++i)
		{
			float length = glm::sqrt(vertexNormals[i * 3 + 0] * vertexNormals[i * 3 + 0] 
						 + vertexNormals[i * 3 + 1] * vertexNormals[i * 3 + 1] 
						 + vertexNormals[i * 3 + 2] * vertexNormals[i * 3 + 2]);

			// Average them
			vertexNormals[i * 3 + 0] /= length;
			vertexNormals[i * 3 + 1] /= length;
			vertexNormals[i * 3 + 2] /= length;
		}
	}

}

