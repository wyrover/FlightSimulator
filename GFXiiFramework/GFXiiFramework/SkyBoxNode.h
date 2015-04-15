#pragma once
#include "ISceneNode.h"
#include "Camera.h"

class SkyBoxNode;

typedef std::shared_ptr<SkyBoxNode> SkyBoxNodePtr;

class SkyBoxNode final : public ISceneNode
{
private:
	CameraPtr				m_pCamera;

public:
							SkyBoxNode(const ActorPtr pActor, const CameraPtr pCamera);
	virtual					~SkyBoxNode() { }

	virtual void			Render() override;

	virtual void			PreRender() override;
};

