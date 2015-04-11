#include "MeshNode.h"
#include "MeshComponent.h"

MeshNode::MeshNode(ActorPtr pActor)
{
	m_pWeakActorPtr = pActor;
}

void MeshNode::Render() const
{
	ActorPtr pActor;

	if (pActor = m_pWeakActorPtr.lock())
	{
		pActor->GetComponent<MeshComponent>()->Render();

		for (const SceneNodePtr &pSceneNode : m_children)
		{
			pSceneNode->Render();
		}
	}
}