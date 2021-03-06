#include "MeshNode.h"
#include "Mesh.h"
#include "Material.h"
#include "Scene.h"

MeshNode::MeshNode(ActorPtr pActor)
{
	m_pActor = pActor;

	if (pActor->GetComponent<Material>()->GetSpecular())
	{
		m_bCalculateSpecular = true;
	}
	else
	{
		m_bCalculateSpecular = false;
	}

	if (pActor->GetComponent<Material>()->GetNormal())
	{
		m_bCalculateNormal = true;
	}
	else
	{
		m_bCalculateNormal = false;
	}
}

void MeshNode::Render()
{
	GetComponent<Mesh>()->Render();

	for (const SceneNodePtr &pSceneNode : m_children)
	{
		pSceneNode->Render();
	}
}

void MeshNode::PreRender()
{
}