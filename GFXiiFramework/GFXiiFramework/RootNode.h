#pragma once
#include "ISceneNode.h"
#include "MeshNode.h"
#include "SkyBoxNode.h"

class RootNode;

typedef std::shared_ptr<RootNode> RootNodePtr;
typedef std::vector<std::shared_ptr<MeshNode>> MeshNodeList;
typedef std::vector<std::shared_ptr<SkyBoxNode>> SkyBoxNodeList;

class RootNode : public ISceneNode
{
protected:
	MeshNodeList					m_meshNodes;
	SkyBoxNodeList					m_skyBoxNodes;

public:
									RootNode() { }
	virtual							~RootNode() { }

	inline void						AddMeshNode(const MeshNodePtr pMeshNode)
	{
		m_meshNodes.push_back(pMeshNode);
	}

	inline void						AddSkyBoxNode(const SkyBoxNodePtr pSkyBoxNode)
	{
		m_skyBoxNodes.push_back(pSkyBoxNode);
	}

	virtual void					Render() override;
	virtual void					PreRender() override;
};

