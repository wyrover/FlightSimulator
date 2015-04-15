#pragma once
#include "ISceneNode.h"

/*
	MeshNode is class that stores data about actors with meshes to be rendered
*/

class MeshNode;

typedef std::shared_ptr<MeshNode> MeshNodePtr;

class MeshNode : public ISceneNode
{
private:
	bool						m_bCalculateSpecular;

public:
								MeshNode(ActorPtr pActor);
	virtual						~MeshNode() { }

	inline const bool			GetCalculateSpecular() const
	{
		return m_bCalculateSpecular;
	}

	virtual void				Render() override;
	virtual void				PreRender() override;
};