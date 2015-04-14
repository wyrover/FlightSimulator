#include "SkyBoxNode.h"
#include "SkyBox.h"
#include "Transform.h"
#include "Scene.h"

SkyBoxNode::SkyBoxNode(ActorPtr pActor)
{
	m_pWeakActorPtr = pActor;
}

void SkyBoxNode::Render()
{
	ActorPtr pActor;

	if (pActor = m_pWeakActorPtr.lock())
	{
		pActor->GetComponent<Transform>()->SetPosition(Scene::GetCamera()->GetOwner()->GetComponent<Transform>()->GetPosition());
		pActor->GetComponent<SkyBox>()->Render();

		for (const SceneNodePtr &pSceneNode : m_children)
		{
			pSceneNode->Render();
		}
	}
}

void SkyBoxNode::PreRender()
{
	ActorPtr pActor;

	if (pActor = m_pWeakActorPtr.lock())
	{
		pActor->GetComponent<Transform>()->SetPosition(Scene::GetCamera()->GetOwner()->GetComponent<Transform>()->GetPosition());
	}

	Scene::GetSkyBoxShaderProgram().UpdateUniformValues(std::make_shared<SkyBoxNode>(*this));
}