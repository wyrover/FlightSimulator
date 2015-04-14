#include "MeshNode.h"
#include "Mesh.h"
#include "Material.h"
#include "Scene.h"

MeshNode::MeshNode(ActorPtr pActor)
{
	m_pWeakActorPtr = pActor;

	if (pActor->GetComponent<Material>()->GetSpecular())
	{
		m_bCalculateSpecular = true;
	}
	else
	{
		m_bCalculateSpecular = false;
	}
}

void MeshNode::Render()
{
	ActorPtr pActor;

	if (pActor = m_pWeakActorPtr.lock())
	{
		pActor->GetComponent<Mesh>()->Render();

		for (const SceneNodePtr &pSceneNode : m_children)
		{
			pSceneNode->Render();
		}
	}
}

void MeshNode::PreRender()
{
	Scene::GetMeshShaderProgram().UpdateUniformValues(std::make_shared<MeshNode>(*this));
}