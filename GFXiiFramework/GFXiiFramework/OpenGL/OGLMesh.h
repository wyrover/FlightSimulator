#pragma once

#include <Windows.h>
#include "OGLTexture.h"
#include "../GameObject.h"
#include "../Triangle.h"

class OGLMesh
{
private:
	unsigned int	m_vao;
	unsigned int	m_vbo_verts;
	int				m_numtriangles;
	//OGLTexture		m_diffuse;
	//OGLTexture		m_specular;

public:
	OGLMesh();
	OGLMesh(LPCWSTR filename);
	OGLMesh(LPCWSTR mesh, const char* diffuse);
	OGLMesh(LPCWSTR mesh, const char* diffuse, const char* specular);
	~OGLMesh();

	void LoadAndBuildMeshFromOBJFile(LPCWSTR filename);

	void Render();

};