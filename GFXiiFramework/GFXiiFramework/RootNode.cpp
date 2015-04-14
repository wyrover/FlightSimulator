#include "RootNode.h"
#include "Scene.h"

void RootNode::Render()
{
	Scene::GetSkyBoxShaderProgram().PreRender();
	for (const SkyBoxNodePtr &pSceneNode : m_skyBoxNodes)
	{
		pSceneNode->PreRender();
		pSceneNode->Render();
	}
	Scene::GetSkyBoxShaderProgram().PostRender();

	Scene::GetMeshShaderProgram().PreRender();
	for (const MeshNodePtr &pSceneNode : m_meshNodes)
	{
		pSceneNode->PreRender();
		pSceneNode->Render();
	}
	Scene::GetMeshShaderProgram().PostRender();
}

void RootNode::PreRender()
{

}