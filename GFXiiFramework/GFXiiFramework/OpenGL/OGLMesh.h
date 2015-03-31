#pragma once

#include <Windows.h>
#include "OGLTexture.h"
#include "../GameObject.h"
#include "../Triangle.h"


class OGLMesh : public GameObject
{
private:
	unsigned int	m_vao;
	unsigned int	m_vbo_verts;
	int				m_numtriangles;
	OGLTexture		m_texture;

public:
	OGLMesh();
	OGLMesh(LPCWSTR filename);
	OGLMesh(LPCWSTR mesh, const char* texture);
	~OGLMesh();

	void LoadAndBuildMeshFromOBJFile(LPCWSTR filename);

	void Render();

};