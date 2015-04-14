#include "Scene.h"
#include "MeshNode.h"
#include "SkyBoxNode.h"
#include "RootNode.h"

CameraPtr Scene::s_pCamera = nullptr;	
MeshShader Scene::s_pMeshShader;
SkyBoxShader Scene::s_pSkyBoxShader;

Scene::Scene()
{
	m_pActors = std::make_shared<std::map<ActorID, ActorPtr>>();

	Init();
}

Scene::Scene(const ActorMap actors)
{
	m_pActors = actors;

	Init();

	CreateScene();
}

void Scene::Init()
{
	m_pRoot = std::make_shared<RootNode>();

	Scene::s_pMeshShader.AttachAndBuildProgram(L"../asset/shader/glsl/mesh.vert", L"../asset/shader/glsl/mesh.frag");
	Scene::s_pSkyBoxShader.AttachAndBuildProgram(L"../asset/shader/glsl/skybox.vert", L"../asset/shader/glsl/skybox.frag");
}

void Scene::CreateScene()
{
	for (const auto actor : *m_pActors)
	{
		switch (actor.second->GetRenderer())
		{
		case Renderer_Mesh:
			m_pRoot->AddMeshNode(std::make_shared<MeshNode>(actor.second));
			break;
		case Renderer_SkyBox:
			m_pRoot->AddSkyBoxNode(std::make_shared<SkyBoxNode>(actor.second));
			break;
		}

		if (!s_pCamera)
		{
			if (actor.second->GetComponent<Camera>())
			{
				s_pCamera = actor.second->GetComponent<Camera>();
			}
		}
		if (!m_pCharacterController)
		{
			if (actor.second->GetComponent<CharacterController>())
			{
				m_pCharacterController = actor.second->GetComponent<CharacterController>();
			}
		}
	}
}