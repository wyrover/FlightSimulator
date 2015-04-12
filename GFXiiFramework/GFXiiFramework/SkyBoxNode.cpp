#include "SkyBoxNode.h"
#include "SkyBox.h"

SkyBoxNode::SkyBoxNode(ActorPtr pActor)
{
	m_pWeakActorPtr = pActor;
}

void SkyBoxNode::Render() const
{
	ActorPtr pActor;

	if (pActor = m_pWeakActorPtr.lock())
	{
		pActor->GetComponent<SkyBox>()->Render();

		for (const SceneNodePtr &pSceneNode : m_children)
		{
			pSceneNode->Render();
		}
	}
}