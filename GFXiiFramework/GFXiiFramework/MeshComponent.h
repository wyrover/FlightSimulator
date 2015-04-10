#pragma once
#include "ActorComponent.h"
#include "OpenGL\OGLMesh.h"

typedef std::shared_ptr<OGLMesh> MeshPtr;
typedef std::weak_ptr<OGLMesh> WeakMeshPtr;

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

	//inline WeakMeshPtr						GetMesh() 
	//{ 
	//	return WeakMeshPtr(m_pMesh); 
	//}
	//inline void								SetMesh(const LPWSTR file)
	//{
	//	m_pMesh->LoadAndBuildMeshFromOBJFile(file);
	//}
};

