#pragma once
#include "ISceneNode.h"

/*
	MeshNode is class that stores data about actors with meshes to be rendered
*/

class MeshNode final : public ISceneNode
{
public:
								MeshNode(ActorPtr pActor);
	virtual						~MeshNode() { }

	void						Render() const override;
};