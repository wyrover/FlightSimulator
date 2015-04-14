#pragma once
#include "ISceneNode.h"

class SkyBoxNode;

typedef std::shared_ptr<SkyBoxNode> SkyBoxNodePtr;

class SkyBoxNode final : public ISceneNode
{
public:
							SkyBoxNode(ActorPtr pActor);
	virtual					~SkyBoxNode() { }

	void					Render() override;

	virtual void			PreRender() override;
};

