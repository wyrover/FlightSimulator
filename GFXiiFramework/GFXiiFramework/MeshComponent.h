#pragma once
#include <Windows.h>
#include "ActorComponent.h"

class MeshComponent : public ActorComponent
{
private:
	unsigned int	m_vao;
	unsigned int	m_vbo_verts;
	int				m_numtriangles;

public:
	MeshComponent();
	virtual ~MeshComponent();

	static const ActorComponentID			COMPONENT_ID = 3;

	inline virtual ActorComponentID			GetComponentID() override
	{
		return COMPONENT_ID;
	}

	void									LoadAndBuildMeshFromOBJFile(LPCWSTR file);
	void									Render();
};

