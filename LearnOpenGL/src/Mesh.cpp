#include "Mesh.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(unsigned int dataType, const void* vbData, unsigned int vbCount, const void* ibData, unsigned int ibCount, std::string layoutName)
	:	mat(nullptr)
{
	va = new VertexArray();
	vb = new VertexBuffer(vbData, sizeof(float) * vbCount);
	VertexBufferLayout layout = Renderer::GetInstance().GetLayout(layoutName);
	va->AssignBuffer(*vb, layout);
	ib = new IndexBuffer(ibData, ibCount);
}

Mesh::~Mesh()
{
	EraseMesh();
}

Mesh::Mesh(const Mesh& rMesh)
{
	va = rMesh.va;
	vb = rMesh.vb;
	ib = rMesh.ib;
	mat = rMesh.mat;
}

Mesh& Mesh::operator=(const Mesh& rMesh)
{
	if (this == &rMesh)
		return *this;

	this->EraseMesh();

	// DeepCopy
}

void Mesh::EraseMesh()
{
	delete ib;
	delete vb;
	delete va;
}

void Mesh::Bind() const
{
	va->Bind();
	vb->Bind();
	ib->Bind();
	mat->Bind();
}

void Mesh::Unbind() const 
{
	ib->Unbind();
	vb->Unbind();
	va->Unbind();
	mat->Unbind();
}

void Mesh::SetMaterial(Material* newMaterial) { mat = newMaterial; }