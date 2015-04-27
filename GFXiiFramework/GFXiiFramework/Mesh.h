#pragma once
#include <Windows.h>
#include "ActorComponent.h"
#include "Triangle.h"

class Mesh;

typedef std::shared_ptr<Mesh> MeshPtr;

class Mesh : public ActorComponent
{
private:
	unsigned int							m_vao;
	unsigned int							m_vbo_verts;
	int										m_numtriangles;

	Triangle								*m_mesh;

public:
											Mesh();
	virtual									~Mesh();

	static const ActorComponentID			COMPONENT_ID = 3;

	inline virtual ActorComponentID			GetComponentID() const override
	{
		return COMPONENT_ID;
	}

	inline Triangle*						GetMesh() const
	{
		return m_mesh;
	}

	inline int								GetTriangleCount() const
	{
		return m_numtriangles;
	}

	void									LoadAndBuildMeshFromOBJFile(LPCWSTR file);
	void									LoadMeshFromTriangles(Triangle* mesh, int count);
	void									Render();
};

