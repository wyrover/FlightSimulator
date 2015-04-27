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

	MeshNodeList						m_meshNodes;
	SkyBoxNodeList						m_skyBoxNodes;
	CameraPtr							m_pCamera;

	BillboardList						m_billboards;

	// TODO: change this to something better
	RigidbodyList						m_rigidbodies;

	int									m_count;
	glm::vec4							m_dayAndNight;

	void								CreateScene(const ActorMap actors);

public:
	Scene();
	Scene(const ActorMap actors);
	~Scene() { }

	void								UpdateDayNightCycle();
	void								UpdatePlayerController();
	void								UpdateRigidbodies();
	void								CheckCollisions();

	void								PreRender();
	void								Render();

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