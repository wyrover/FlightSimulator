#pragma once
#include "ISceneNode.h"
#include "Camera.h"
#include "CharacterController.h"
#include "SkyBox.h"
#include "Actor.h"
#include "MeshShader.h"
#include "SkyBoxShader.h"
#include "Rigidbody.h"
#include "BillboardShader.h"
#include "Billboard.h"

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
	BillboardShaderPtr					m_pBillboardShader;

	CharacterControllerPtr				m_pCharacterController;
	ActorMap							m_pActors;

	MeshNodeList						m_meshNodes;
	SkyBoxNodeList						m_skyBoxNodes;
	LightNodePtr						m_pLight;
	CameraPtr							m_pCamera;

	BillboardList						m_billboards;

	// TODO: change this to something better
	RigidbodyList						m_rigidbodies;

	void								CreateScene();

public:
	Scene();
	Scene(const ActorMap actors);
	~Scene() { }

	void								Render()
	{
		// Update player
		m_pCharacterController->Update();

		// Collision detection
		// TODO: change to something better
		for (const RigidbodyPtr &pRigidbody : m_rigidbodies)
		{
			pRigidbody->Update();
		}

		for (unsigned index = 1; index < m_rigidbodies.size(); index++)
		{
			if (m_rigidbodies[0]->GetCollider()->CollisionDetection(m_rigidbodies[index]->GetCollider()))
			{
				m_meshNodes[0]->GetComponent<Transform>()->MoveForward(-1);
				m_meshNodes[0]->GetComponent<Camera>()->Update();
			}
		}

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

		m_pBillboardShader->PreRender(m_pCamera);
		for (const BillboardPtr &pBillboard : m_billboards)
		{
			m_pBillboardShader->UpdateUniformValues(pBillboard);

			pBillboard->Render();
		}
		m_pBillboardShader->PostRender();
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