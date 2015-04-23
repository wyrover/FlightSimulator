#include "SkyBoxNode.h"
#include "SkyBox.h"
#include "Transform.h"
#include "Scene.h"

SkyBoxNode::SkyBoxNode(const ActorPtr pActor, const CameraPtr pCamera)
{
	m_pCamera = pCamera;
	m_pActor = pActor;
}

void SkyBoxNode::Render()
{
	GetComponent<SkyBox>()->Render();

	for (const SceneNodePtr &pSceneNode : m_children)
	{
		pSceneNode->Render();
	}
}

void SkyBoxNode::PreRender()
{
	GetComponent<Transform>()->SetPosition(m_pCamera->GetPosition());
}