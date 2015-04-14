#pragma once
#include "ISceneNode.h"
#include "Camera.h"
#include "CharacterController.h"
#include "SkyBox.h"
#include "Actor.h"
#include "GLSLShader.h"
#include "MeshShader.h"
#include "SkyBoxShader.h"
#include "RootNode.h"

class Scene;

typedef std::shared_ptr<std::map<ActorID, ActorPtr>> ActorMap;
typedef std::shared_ptr<Scene> ScenePtr;

class Scene final
{
private:
	static CameraPtr					s_pCamera;
	static MeshShader					s_pMeshShader;
	static SkyBoxShader					s_pSkyBoxShader;

	RootNodePtr							m_pRoot;
	CharacterControllerPtr				m_pCharacterController;
	SkyBoxPtr							m_pSkyBox;
	ActorMap							m_pActors;

	void								CreateScene();

public:
	Scene();
	Scene(const ActorMap actors);
	~Scene() { }

	inline void							Render() const
	{
		// Update player
		m_pCharacterController->Update();

		// Render meshes
		m_pRoot->Render();
	}

	inline void							SetRoot(const RootNodePtr pRoot)
	{
		m_pRoot = pRoot;
	}

	inline SceneNodePtr					GetRoot() const
	{
		return m_pRoot;
	}

	inline void							SetSkyBox(SkyBoxPtr pSkyBox)
	{
		m_pSkyBox = pSkyBox;
	}

	inline void							SetCharacterController(CharacterControllerPtr pCharacterController)
	{
		m_pCharacterController = pCharacterController;
	}

	inline void							SetCamera(const CameraPtr pCamera)
	{
		s_pCamera = pCamera;
	}

	inline static const CameraPtr		GetCamera()
	{
		return s_pCamera;
	}

	inline static MeshShader&			GetMeshShaderProgram()
	{
		return s_pMeshShader;
	}

	inline static SkyBoxShader&			GetSkyBoxShaderProgram()
	{
		return s_pSkyBoxShader;
	}

	void								Init();
};