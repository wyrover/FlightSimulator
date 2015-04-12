#include "Mesh.h"
#include "GLEW\include\glew.h"
#include "OBJFileReader.h"
#include "Material.h"
#include "Shader.h"
#include "Actor.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::Render()
{
	m_pOwner->GetComponent<Shader>()->PreRender();

	unsigned int difHandle = m_pOwner->GetComponent<Material>()->GetDiffuse().m_syshandle;
	unsigned int specHandle = m_pOwner->GetComponent<Material>()->GetSpecular().m_syshandle;
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, difHandle);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specHandle);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glDrawArrays(GL_TRIANGLES, 0, m_numtriangles * 3);

	glBindVertexArray(0);

	m_pOwner->GetComponent<Shader>()->PostRender();
}

void Mesh::LoadAndBuildMeshFromOBJFile(LPCWSTR filename)
{
	Triangle* mesh;

	m_numtriangles = importOBJMesh(filename, &mesh);

	int offset = sizeof(Vector3);
	int stride = sizeof(Vertex);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo_verts);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glBufferData(GL_ARRAY_BUFFER, 3 * m_numtriangles * sizeof(Vertex), &(mesh[0].m_vertices[0].m_position[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + offset));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + 2 * offset));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	delete[] mesh;
}