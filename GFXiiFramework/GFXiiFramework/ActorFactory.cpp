#include <Windows.h>
#include "ActorFactory.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "CharacterController.h"
#include "SkyBox.h"
#include "Light.h"
#include "Rigidbody.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Billboard.h"

#define CAMERA "CameraComponent"
#define CHARACTER_CONTROLLER "CharacterControllerComponent"
#define SKY_BOX "SkyBoxComponent"
#define MATERIAL "MaterialComponent"
#define MESH "MeshComponent"
#define TRANSFORM "TransformComponent"
#define LIGHT "LightComponent"
#define RIGIDBODY "RigidbodyComponent"
#define BILLBOARD "BillboardComponent"

ActorFactory::ActorFactory() : m_currentActorID{ 0 }
{
	m_pActors = std::make_shared<std::map<ActorID, ActorPtr>>();
}

ActorFactory::~ActorFactory()
{
}

const ActorMap ActorFactory::CreateActorsFromDOM(const DocumentObjectModelPtr pDOM)
{
	if (pDOM->GetRoot()->name == "ActorFactory")
	{
		for (const TagNodePtr &pTagNode : pDOM->GetRoot()->children)
		{
			CreateNewActor(pTagNode);
		}
	}
	else
	{
		assert(false);
	}

	return m_pActors;
}

void ActorFactory::CreateNewActor(const TagNodePtr pTagNode)
{
	if (pTagNode->name == "Actor")
	{
		ActorPtr pActor = std::make_shared<Actor>(m_currentActorID, GetRenderer(pTagNode));

		// Add components
		for (const TagNodePtr &pComponent : pTagNode->children)
		{
			AddNewComponent(pActor, pComponent);
		}

		// Add to actor map
		(*m_pActors)[m_currentActorID++] = pActor;
	}
	else
	{
		// something went wrong
		assert(false);
	}
}

// Hardcoded just to get projectiles working
ActorPtr ActorFactory::CreateActorFromPrefab(const ActorPtr pActorPrefab)
{
	ActorPtr pActor = std::make_shared<Actor>(m_currentActorID, pActorPrefab->GetRenderer());

	TransformPtr pTransform = std::make_shared<Transform>();
	pTransform->SetUp(pActorPrefab->GetComponent<Transform>()->GetUpVector());
	pTransform->SetRight(pActorPrefab->GetComponent<Transform>()->GetRightVector());
	pTransform->SetView(pActorPrefab->GetComponent<Transform>()->GetViewVector());

	MeshPtr pMesh = std::make_shared<Mesh>();
	pMesh->LoadMeshFromTriangles(pActorPrefab->GetComponent<Mesh>()->GetMesh(), pActorPrefab->GetComponent<Mesh>()->GetTriangleCount());

	MaterialPtr pMaterial = std::make_shared<Material>();
	pMaterial->SetDiffuse("../asset/texture/missile.tga");

	RigidbodyPtr pRigidbody = std::make_shared<Rigidbody>();

	SphereColliderPtr pCollider = std::make_shared<SphereCollider>();
	pCollider->SetSize(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);

	pRigidbody->SetCollider(pCollider);
	
	pTransform->SetOwner(pActor);
	pMesh->SetOwner(pActor);
	pMaterial->SetOwner(pActor);
	pRigidbody->SetOwner(pActor);

	pActor->AddComponent(pTransform);
	pActor->AddComponent(pMesh);
	pActor->AddComponent(pMaterial);
	pActor->AddComponent(pRigidbody);

	m_currentActorID++;

	return pActor;
}

const Renderer ActorFactory::GetRenderer(const TagNodePtr pTagNode) const
{
	std::string attribute = pTagNode->data["renderer"];

	if (attribute == "mesh")
	{
		return Renderer_Mesh;
	}
	else if (attribute== "skybox")
	{
		return Renderer_SkyBox;
	}
	else if (attribute == "light")
	{
		return Renderer_Light;
	}
	else if (attribute == "pass")
	{
		return Renderer_Pass;
	}
	else if (attribute == "billboard")
	{
		return Renderer_Billboard;
	}
	else if (attribute == "projectilePrefab")
	{
		return Renderer_ProjectilePrefab;
	}
	// Something went wrong
	assert(false);
	
	return Renderer_Pass;
}

void ActorFactory::AddNewComponent(ActorPtr pActor, const TagNodePtr pTagNode) const
{
	std::string component = pTagNode->name;

	if (component == TRANSFORM)
	{
		AddNewTransformComponent(pActor, pTagNode);
	}
	else if (component == MESH)
	{
		AddNewMeshComponent(pActor, pTagNode);
	}
	else if (component == MATERIAL)
	{
		AddNewMaterialComponent(pActor, pTagNode);
	}
	else if (component == SKY_BOX)
	{
		AddNewSkyBoxComponent(pActor, pTagNode);
	}
	else if (component == CHARACTER_CONTROLLER)
	{
		AddNewCharacterControllerComponent(pActor, pTagNode);
	}
	else if (component == CAMERA)
	{
		AddNewCameraComponent(pActor, pTagNode);
	}
	else if (component == LIGHT)
	{
		AddNewLightComponent(pActor, pTagNode);
	}
	else if (component == RIGIDBODY)
	{
		AddNewRigidbodyComponent(pActor, pTagNode);
	}
	else if (component == BILLBOARD)
	{
		AddNewBillboardComponent(pActor, pTagNode);
	}
	else
	{
		// This shouldn't happen
		assert(false);
	}
}

const glm::vec3 ActorFactory::GetXYZ(std::map<std::string, std::string> data) const
{
	float x, y, z;

	x = (float)atof(data["X"].c_str());
	y = (float)atof(data["Y"].c_str());
	z = (float)atof(data["Z"].c_str());

	return glm::vec3(x, y, z);
}

const glm::vec3 ActorFactory::GetRGB(std::map<std::string, std::string> data) const
{
	float x, y, z;

	x = (float)atof(data["R"].c_str());
	y = (float)atof(data["G"].c_str());
	z = (float)atof(data["B"].c_str());

	return glm::vec3(x, y, z);
}

void ActorFactory::AddNewTransformComponent(ActorPtr pActor, const TagNodePtr pTagNode) const
{
	TransformPtr pTransform = std::make_shared<Transform>();

	for (const TagNodePtr &pTag : pTagNode->children)
	{
		std::string attribute = pTag->name;

		if (attribute == "Position")
		{
			pTransform->SetPosition(GetXYZ(pTag->data));
		}
		else if (attribute == "Up")
		{
			pTransform->SetUp(GetXYZ(pTag->data));
		}
		else if (attribute == "Right")
		{
			pTransform->SetRight(GetXYZ(pTag->data));
		}
		else if (attribute == "View")
		{
			pTransform->SetView(GetXYZ(pTag->data));
		}
		else if (attribute == "Scale")
		{
			std::string scaleType = pTag->data["uniform"];

			if (scaleType != "")
			{
				pTransform->SetUniformScale((float)atof(pTag->data["uniform"].c_str()));
			}
			else
			{
				glm::vec3 scale = GetXYZ(pTag->data);
				pTransform->SetScale(scale.x, scale.y, scale.z);
			}
		}
		else if (attribute == "Rotation")
		{
			float yaw, pitch, roll;

			yaw = (float)atof(pTag->data["yaw"].c_str());
			pitch = (float)atof(pTag->data["pitch"].c_str());
			roll = (float)atof(pTag->data["roll"].c_str());

			pTransform->Rotation(yaw, pitch, roll);
		}
		else
		{
			// XML is wrong
			assert(false);
		}
	}

	pTransform->SetOwner(pActor);
	pActor->AddComponent(pTransform);
}

void ActorFactory::AddNewMeshComponent(ActorPtr pActor, const TagNodePtr pTagNode) const
{
	MeshPtr pMesh = std::make_shared<Mesh>();

	for (const TagNodePtr &pTag : pTagNode->children)
	{
		std::string attribute = pTag->name;

		if (attribute == "Model")
		{
			std::string dir = pTag->data["dir"];
			std::wstring wDir(dir.begin(), dir.end());

			const wchar_t *directory = wDir.c_str();

			pMesh->LoadAndBuildMeshFromOBJFile(directory);
		}
		else
		{
			assert(false);
		}
	}

	pMesh->SetOwner(pActor);
	pActor->AddComponent(pMesh);
}

void ActorFactory::AddNewMaterialComponent(ActorPtr pActor, const TagNodePtr pTagNode) const
{
	MaterialPtr pMaterial = std::make_shared<Material>();

	for (const TagNodePtr &pTag : pTagNode->children)
	{
		std::string attribute = pTag->name;

		if (attribute == "Diffuse")
		{
			const char* directory = pTag->data["dir"].c_str();

			pMaterial->SetDiffuse(directory);
		}
		else if (attribute == "Specular")
		{
			const char* directory = pTag->data["dir"].c_str();

			pMaterial->SetSpecular(directory);
		}
		else if (attribute == "Normal")
		{
			const char* directory = pTag->data["dir"].c_str();

			pMaterial->SetNormal(directory);
		}
		else
		{
			// Something went wrong
			assert(false);
		}
	}

	pMaterial->SetOwner(pActor);
	pActor->AddComponent(pMaterial);
}

void ActorFactory::AddNewCharacterControllerComponent(ActorPtr pActor, const TagNodePtr pTagNode) const
{
	CharacterControllerPtr pController = std::make_shared<CharacterController>();

	pController->SetOwner(pActor);
	pActor->AddComponent(pController);
}

void ActorFactory::AddNewCameraComponent(ActorPtr pActor, const TagNodePtr pTagNode) const
{
	CameraPtr pCamera = std::make_shared<Camera>();

	pCamera->SetOwner(pActor);
	pActor->AddComponent(pCamera);
}

void ActorFactory::AddNewSkyBoxComponent(ActorPtr pActor, const TagNodePtr pTagNode) const
{
	SkyBoxPtr pSkyBox = std::make_shared<SkyBox>();

	std::map<std::string, const char*> faces;

	for (const TagNodePtr &pTag : pTagNode->children)
	{
		std::string attribute = pTag->name;

		if (attribute == "Front" || attribute == "Back" || attribute == "Left" || attribute == "Right" || attribute == "Top" || attribute == "Bottom")
		{
			faces[pTag->name] = pTag->data["dir"].c_str();
		}
		else
		{
			// Something went wrong
			assert(false);
		}
	}

	pSkyBox->Init(faces["Front"], faces["Back"], faces["Left"], faces["Right"], faces["Top"], faces["Bottom"]);
	pSkyBox->SetOwner(pActor);
	pActor->AddComponent(pSkyBox);
}

void ActorFactory::AddNewLightComponent(ActorPtr pActor, const TagNodePtr pTagNode) const
{
	LightPtr pLight = std::make_shared<Light>();

	for (const TagNodePtr &pTag : pTagNode->children)
	{
		std::string attribute = pTag->name;

		if (attribute == "Colour")
		{
			pLight->SetColour(GetRGB(pTag->data));
		}
		else
		{
			// Shouldn't happen
			assert(false);
		}
	}

	pLight->SetOwner(pActor);
	pActor->AddComponent(pLight);
}

void ActorFactory::AddNewRigidbodyComponent(ActorPtr pActor, const TagNodePtr pTagNode) const
{
	RigidbodyPtr pRigidbody = std::make_shared<Rigidbody>();

	for (const TagNodePtr &pTag : pTagNode->children)
	{
		std::string attribute = pTag->name;

		if (attribute == "Collider")
		{
			std::string type = pTag->data["Type"];

			if (type == "Box")
			{

			}
			else if (type == "Sphere")
			{
				SphereColliderPtr pCollider = std::make_shared<SphereCollider>();
				pCollider->SetSize(glm::vec3(0.0f, 0.0f, 0.0f), (float)atof(pTag->data["Radius"].c_str()));

				pRigidbody->SetCollider(pCollider);
			}
			else
			{
				assert(false);
			}

		}
		else
		{
			assert(false);
		}
	}

	pRigidbody->SetOwner(pActor);
	pActor->AddComponent(pRigidbody);
}

void ActorFactory::AddNewBillboardComponent(ActorPtr pActor, const TagNodePtr pTagNode) const
{
	BillboardPtr pBillboard = std::make_shared<Billboard>();

	pBillboard->SetOwner(pActor);
	pActor->AddComponent(pBillboard);
}