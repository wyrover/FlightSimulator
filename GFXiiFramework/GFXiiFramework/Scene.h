#pragma once
#include "MeshNode.h"
#include "CameraComponent.h"

class Scene final
{
private:
	SceneNodePtr				m_pRoot;
	CameraPtr					m_pCamera;

public:
	Scene() { }
	~Scene() { }

	inline void					Render() const
	{
		m_pRoot->Render();
	}

	inline void					SetRoot(const SceneNodePtr pRoot)
	{
		m_pRoot = pRoot;
	}

	inline void					SetCamera(const CameraPtr pCamera)
	{
		m_pCamera = pCamera;
	}

	inline const CameraPtr		GetCamera() const
	{
		return m_pCamera;
	}
};

