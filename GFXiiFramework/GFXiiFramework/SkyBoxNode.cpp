#include "SkyBoxNode.h"
#include "SkyBoxComponent.h"

SkyBoxNode::SkyBoxNode(ActorPtr pActor)
{
	m_pWeakActorPtr = pActor;
}

void SkyBoxNode::Render() const
{
	ActorPtr pActor;

	if (pActor = m_pWeakActorPtr.lock())
	{
		pActor->GetComponent<SkyBoxComponent>()->Render();

		for (const SceneNodePtr &pSceneNode : m_children)
		{
			pSceneNode->Render();
		}
	}
}