#pragma once
#include <Windows.h>
#include "ActorComponent.h"

class Mesh;

typedef std::shared_ptr<Mesh> MeshPtr;

class Mesh : public ActorComponent
{
private:
	unsigned int							m_vao;
	unsigned int							m_vbo_verts;
	int										m_numtriangles;

public:
											Mesh();
	virtual									~Mesh();

	static const ActorComponentID			COMPONENT_ID = 3;

	inline virtual ActorComponentID			GetComponentID() const override
	{
		return COMPONENT_ID;
	}

	void									LoadAndBuildMeshFromOBJFile(LPCWSTR file);
	void									Render();
};

