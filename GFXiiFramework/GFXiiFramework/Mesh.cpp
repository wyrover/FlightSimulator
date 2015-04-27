#include "Mesh.h"
#include "GLEW\include\glew.h"
#include "OBJFileReader.h"
#include "Material.h"
#include "Actor.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::Render()
{
	unsigned int difHandle = GetComponent<Material>()->GetDiffuse()->m_syshandle;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, difHandle);

	if (m_pOwner->GetComponent<Material>()->GetSpecular())
	{
		unsigned int specHandle = GetComponent<Material>()->GetSpecular()->m_syshandle;

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specHandle);
	}

	if (m_pOwner->GetComponent<Material>()->GetNormal())
	{
		unsigned int normHandle = GetComponent<Material>()->GetNormal()->m_syshandle;

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, normHandle);
	}

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glDrawArrays(GL_TRIANGLES, 0, m_numtriangles * 3);

	glBindVertexArray(0);
}

void Mesh::LoadMeshFromTriangles(Triangle* mesh, int count)
{
	m_mesh = mesh;
	m_numtriangles = count;

	int offset = sizeof(Vector3);
	int stride = sizeof(Vertex);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo_verts);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glBufferData(GL_ARRAY_BUFFER, 3 * m_numtriangles * sizeof(Vertex), &(m_mesh[0].m_vertices[0].m_position[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + offset));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + 2 * offset));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + 3 * offset));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

void Mesh::LoadAndBuildMeshFromOBJFile(LPCWSTR filename)
{
	m_numtriangles = importOBJMesh(filename, &m_mesh);

	int offset = sizeof(Vector3);
	int stride = sizeof(Vertex);

	for (int i = 0; i < m_numtriangles; i++)
	{
		m_mesh[i].GenerateTanget();
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo_verts);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glBufferData(GL_ARRAY_BUFFER, 3 * m_numtriangles * sizeof(Vertex), &(m_mesh[0].m_vertices[0].m_position[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + offset));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + 2 * offset));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + 3 * offset));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}