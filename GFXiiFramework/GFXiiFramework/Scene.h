#pragma once
#include "ISceneNode.h"
#include "Camera.h"
#include "CharacterController.h"
#include "SkyBox.h"
#include "Actor.h"
#include "MeshShader.h"
#include "SkyBoxShader.h"

class Scene;

typedef std::shared_ptr<std::map<ActorID, ActorPtr>> ActorMap;
typedef std::shared_ptr<Scene> ScenePtr;

typedef std::vector<MeshNodePtr> MeshNodeList;
typedef std::vector<SkyBoxNodePtr> SkyBoxNodeList;
typedef std::vector<LightNodePtr> LightNodeList;

class Scene final
{
private:
	MeshShaderPtr						m_pMeshShader;
	SkyBoxShaderPtr						m_pSkyBoxShader;

	CharacterControllerPtr				m_pCharacterController;
	ActorMap							m_pActors;

	MeshNodeList						m_meshNodes;
	SkyBoxNodeList						m_skyBoxNodes;
	LightNodePtr						m_pLight;
	CameraPtr							m_pCamera;

	void								CreateScene();

public:
	Scene();
	Scene(const ActorMap actors);
	~Scene() { }

	inline void							Render()
	{
		// Update player
		m_pCharacterController->Update();

		m_pSkyBoxShader->PreRender(m_pCamera);
		for (const SkyBoxNodePtr &pSceneNode : m_skyBoxNodes)
		{
			m_pSkyBoxShader->UpdateUniformValues(pSceneNode);

			pSceneNode->Render();
		}
		m_pSkyBoxShader->PostRender();
		
		m_pMeshShader->PreRender(m_pCamera, m_pLight);
		for (const MeshNodePtr &pSceneNode : m_meshNodes)
		{
			m_pMeshShader->UpdateUniformValues(pSceneNode);

			pSceneNode->Render();
		}
		m_pMeshShader->PostRender();
	}

	inline void						SetCharacterController(CharacterControllerPtr pCharacterController)
	{
		m_pCharacterController = pCharacterController;
	}

	inline void						AddMeshNode(const MeshNodePtr pMeshNode)
	{
		m_meshNodes.push_back(pMeshNode);
	}

	inline void						AddSkyBoxNode(const SkyBoxNodePtr pSkyBoxNode)
	{
		m_skyBoxNodes.push_back(pSkyBoxNode);
	}

	inline void						SetLight(const LightNodePtr pLight)
	{
		m_pLight = pLight;
	}

	inline const LightNodePtr		GetLight() const
	{
		return m_pLight;
	}

	inline void						SetCamera(const CameraPtr pCamera)
	{
		m_pCamera = pCamera;
	}

	inline const CameraPtr			GetCamera() const
	{
		return m_pCamera;
	}

	void								Init();
};