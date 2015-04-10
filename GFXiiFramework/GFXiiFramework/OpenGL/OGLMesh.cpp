#include <Windows.h>
#include "OGLMesh.h"
#include "../Triangle.h"
#include "../OBJFileReader.h"
#include "OGLTexture.h"
#include "GLEW/include/glew.h"

OGLMesh::OGLMesh()
{

}

OGLMesh::OGLMesh(LPCWSTR filename)
{
	LoadAndBuildMeshFromOBJFile(filename);
}

OGLMesh::OGLMesh(LPCWSTR mesh, const char* diffuse) : OGLMesh(mesh)
{
	//m_diffuse.CreateTextureFromFile(diffuse);
	//SetDiffuse(&m_diffuse);
}

OGLMesh::OGLMesh(LPCWSTR mesh, const char* diffuse, const char* specular) : OGLMesh(mesh, diffuse)
{
	//m_specular.CreateTextureFromFile(specular);
	//SetSpecular(&m_specular);
}

OGLMesh::~OGLMesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo_verts);
}

void OGLMesh::Render()
{
	//unsigned int difHandle = dynamic_cast<OGLTexture*>(m_dif)->m_syshandle;

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, difHandle);

	//if (m_spec != nullptr)
	//{
	//	unsigned int specHandle = dynamic_cast<OGLTexture*>(m_spec)->m_syshandle;

	//	glActiveTexture(GL_TEXTURE1);
	//	glBindTexture(GL_TEXTURE_2D, specHandle);
	//}

	

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glDrawArrays(GL_TRIANGLES, 0, m_numtriangles*3);

	glBindVertexArray(0);
}

void OGLMesh::LoadAndBuildMeshFromOBJFile(LPCWSTR filename)
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