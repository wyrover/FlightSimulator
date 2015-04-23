#pragma once
#include "ActorComponent.h"
#include <vector>

class Billboard;

typedef std::shared_ptr<Billboard> BillboardPtr;
typedef std::vector<BillboardPtr> BillboardList;

class Billboard : public ActorComponent
{
protected:
	struct SimpleVertex
	{
		float position[3];
		float colour[3];
		float uv[2];
	};

	unsigned int	m_vao;
	unsigned int	m_vbo_verts;
	unsigned int	m_vbo_indices;

public:
	Billboard() 
	{ 
		Init();
	}

	virtual									~Billboard() { }

	static const ActorComponentID			COMPONENT_ID = 9;

	inline virtual ActorComponentID			GetComponentID() const override { return COMPONENT_ID; }

	void									Init();

	void									Render();
};

