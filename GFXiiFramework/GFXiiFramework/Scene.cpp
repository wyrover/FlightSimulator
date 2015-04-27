#include "Scene.h"
#include "MeshNode.h"
#include "SkyBoxNode.h"
#include "Mesh.h"
	
Scene::Scene()
{
	Init();
}

Scene::Scene(const ActorMap actors)
{
	Init();

	CreateScene(actors);
}

void Scene::Init()
{
	m_count = 0;
	m_dayAndNight = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Assign shaders
	m_pMeshShader = std::make_shared<MeshShader>();
	m_pSkyBoxShader = std::make_shared<SkyBoxShader>();
	m_pBillboardShader = std::make_shared<BillboardShader>();

	// Initialise shaders
	m_pMeshShader->AttachAndBuildProgram(L"../asset/shader/glsl/mesh.vert", L"../asset/shader/glsl/mesh.frag");
	m_pSkyBoxShader->AttachAndBuildProgram(L"../asset/shader/glsl/skybox.vert", L"../asset/shader/glsl/skybox.frag");
	m_pBillboardShader->AttachAndBuildProgram(L"../asset/shader/glsl/billboard.vert", L"../asset/shader/glsl/billboard.frag");
}

void Scene::CreateScene(const ActorMap actors)
{
	for (const auto actor : *actors)
	{
		// Place nodes into associated category
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
		case Renderer_Billboard:
			m_billboards.push_back(actor.second->GetComponent<Billboard>());
			break;
		case Renderer_ProjectilePrefab:
			m_pCharacterController->SetProjectilePrefab(actor.second);
			break;
		}

		// Assign camera and character controller
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

void Scene::UpdateDayNightCycle()
{
	m_count++;

	if (m_count >= (48 * 60))
	{
		m_count = 0;
	}

	if (m_count < (24 * 60))
	{
		m_dayAndNight.r -= (0.9f / (24.0f * 60.0f));
		m_dayAndNight.g -= (0.9f / (24.0f * 60.0f));
		m_dayAndNight.b -= (0.5f / (24.0f * 60.0f));
	}
	else
	{
		m_dayAndNight.r += (0.9f / (24.0f * 60.0f));
		m_dayAndNight.g += (0.9f / (24.0f * 60.0f));
		m_dayAndNight.b += (0.5f / (24.0f * 60.0f));
	}
}

void Scene::UpdatePlayerController()
{	
	// Update player
	ActorPtr pActor = m_pCharacterController->Update();

	if (pActor != nullptr)
	{
		m_meshNodes.push_back(std::make_shared<MeshNode>(pActor));
	}
}

void Scene::UpdateRigidbodies()
{
	ActorPtr pActor = m_pCharacterController->UpdateProjectiles();

	if (pActor != nullptr)
	{
		for (unsigned i = 1; i < m_meshNodes.size(); i++)
		{
			if (m_meshNodes[i]->GetComponent<Rigidbody>() == pActor->GetComponent<Rigidbody>())
			{
				m_meshNodes.erase(m_meshNodes.begin() + i);
				break;
			}
		}
	}

	// Collision detection
	for (const RigidbodyPtr &pRigidbody : m_rigidbodies)
	{
		pRigidbody->Update();
	}
}

void Scene::CheckCollisions()
{
	// TODO: Re-write this because its fucking dreadful

	for (unsigned index = 1; index < m_rigidbodies.size(); index++)
	{
		if (m_rigidbodies[0]->GetCollider()->CollisionDetection(m_rigidbodies[index]->GetCollider()))
		{
			m_meshNodes[0]->GetComponent<Transform>()->MoveForward(-1);
			m_meshNodes[0]->GetComponent<Camera>()->Update();
		}
	}

	// Note: This is a bit of a hack just so that only the missiles collisions are tested
	for (ActorPtr &pActor : m_pCharacterController->GetProjectilesList())
	{
		for (unsigned index = 1; index < m_rigidbodies.size(); index++)
		{
			if (pActor->GetComponent<Rigidbody>()->GetCollider()->CollisionDetection(m_rigidbodies[index]->GetCollider()))
			{
				// Remove nodes
				for (unsigned i = 1; i < m_meshNodes.size(); i++)
				{
					if (m_meshNodes[i]->GetComponent<Rigidbody>() == m_rigidbodies[index])
					{
						m_meshNodes.erase(m_meshNodes.begin() + i);
					}
					else if (m_meshNodes[i]->GetComponent<Rigidbody>() == pActor->GetComponent<Rigidbody>())
					{
						m_meshNodes.erase(m_meshNodes.begin() + i);
					}
				}

				m_rigidbodies.erase(std::find(m_rigidbodies.begin(), m_rigidbodies.end(), m_rigidbodies[index]));
				m_pCharacterController->RemoveProjectile(pActor);

				// Only remove one projectile and object otherwise it'll crash
				return;
			}
		}
	}
}

void Scene::PreRender()
{
	UpdateDayNightCycle();
	UpdatePlayerController();
	UpdateRigidbodies();
	CheckCollisions();
}

void Scene::Render()
{
	// Render sky box first
	m_pSkyBoxShader->PreRender(m_pCamera, m_dayAndNight);
	for (const SkyBoxNodePtr &pSceneNode : m_skyBoxNodes)
	{
		m_pSkyBoxShader->UpdateUniformValues(pSceneNode);

		pSceneNode->Render();
	}
	m_pSkyBoxShader->PostRender();

	// Render meshes
	m_pMeshShader->PreRender(m_pCamera, m_dayAndNight);
	for (const MeshNodePtr &pSceneNode : m_meshNodes)
	{
		m_pMeshShader->UpdateUniformValues(pSceneNode);

		pSceneNode->Render();
	}
	m_pMeshShader->PostRender();

	// Render billboards;
	m_pBillboardShader->PreRender(m_pCamera, m_dayAndNight);
	for (const BillboardPtr &pBillboard : m_billboards)
	{
		m_pBillboardShader->UpdateUniformValues(pBillboard);

		pBillboard->Render();
	}
	m_pBillboardShader->PostRender();
}