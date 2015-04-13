#pragma once
#include "MeshNode.h"
#include "Camera.h"
#include "CharacterController.h"
#include "SkyBox.h"

class Scene;

typedef std::shared_ptr<Scene> ScenePtr;

class Scene final
{
private:
	SceneNodePtr				m_pRoot;
	CharacterControllerPtr		m_pCharacterController;
	SkyBoxPtr					m_pSkyBox;
	CameraPtr					m_pCamera;

public:
	Scene() { }
	~Scene() { }

	inline void					Render() const
	{
		// Update player
		m_pCharacterController->Update();

		// Render skyBox;
		m_pSkyBox->GetOwner()->GetComponent<Transform>()->SetPosition(m_pCamera->GetOwner()->GetComponent<Transform>()->GetPosition());
		m_pSkyBox->Render();

		// Render meshes
		m_pRoot->Render();
	}

	inline void					SetRoot(const SceneNodePtr pRoot)
	{
		m_pRoot = pRoot;
	}

	inline void					SetSkyBox(SkyBoxPtr pSkyBox)
	{
		m_pSkyBox = pSkyBox;
	}

	inline void					SetCharacterController(CharacterControllerPtr pCharacterController)
	{
		m_pCharacterController = pCharacterController;
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

