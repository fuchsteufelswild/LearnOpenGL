#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"

#include <string>

class Mesh
{
private:
	VertexArray* va;
	VertexBuffer* vb;
	IndexBuffer* ib;
	Material* mat;

	float m_DiffuseConstant;
	float m_SpecularConstant;
public:

	Mesh(unsigned int dataType, const void* vbData, unsigned int vbCount, const void* ibData, unsigned int ibCount, std::string layoutName);
	Mesh(const Mesh& rMesh);
	~Mesh();

	void Bind() const;
	void Unbind() const;

	void EraseMesh();

	inline unsigned int GetIBCount() const { return ib->GetCount(); }
	inline Material* GetMaterial() { return mat; }
	inline float GetDiffuseConstant() const { return m_DiffuseConstant; }
	inline float GetSpecularConstant() const { return m_SpecularConstant; }

	void SetMaterial(Material* newMaterial);

	Mesh& operator=(const Mesh& rMesh);
};