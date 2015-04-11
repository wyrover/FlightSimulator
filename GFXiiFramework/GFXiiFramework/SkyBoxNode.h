#pragma once
#include "ISceneNode.h"


class SkyBoxNode final : public ISceneNode
{
public:
							SkyBoxNode(ActorPtr pActor);
	virtual					~SkyBoxNode() { }

	void					Render() const override;
};

