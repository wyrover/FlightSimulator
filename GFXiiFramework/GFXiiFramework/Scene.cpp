#include "Scene.h"
#include "MeshNode.h"
#include "SkyBoxNode.h"
	
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
	m_pMeshShader = std::make_shared<MeshShader>();
	m_pSkyBoxShader = std::make_shared<SkyBoxShader>();
	m_pBillboardShader = std::make_shared<BillboardShader>();

	m_pMeshShader->AttachAndBuildProgram(L"../asset/shader/glsl/mesh.vert", L"../asset/shader/glsl/mesh.frag");
	m_pSkyBoxShader->AttachAndBuildProgram(L"../asset/shader/glsl/skybox.vert", L"../asset/shader/glsl/skybox.frag");
	m_pBillboardShader->AttachAndBuildProgram(L"../asset/shader/glsl/billboard.vert", L"../asset/shader/glsl/billboard.frag");
}

void Scene::CreateScene()
{
	for (const auto actor : *m_pActors)
	{
		switch (actor.second->GetRenderer())
		{
		case Renderer_Mesh:
			AddMeshNode(std::make_shared<MeshNode>(actor.second));

			if (actor.second->GetComponent<Rigidbody>())
			{
				m_rigidbodies.push_back(actor.second->GetComponent<Rigidbody>());
			}

			break;
		case Renderer_SkyBox:
			AddSkyBoxNode(std::make_shared<SkyBoxNode>(actor.second, m_pCamera));
			break;
		case Renderer_Light:
			SetLight(std::make_shared<LightNode>(actor.second));
			break;
		case Renderer_Billboard:
			m_billboards.push_back(actor.second->GetComponent<Billboard>());
		}

		if (!m_pCamera)
		{
			if (actor.second->GetComponent<Camera>())
			{
				SetCamera(actor.second->GetComponent<Camera>());
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