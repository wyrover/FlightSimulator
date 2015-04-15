#pragma once
#include "ISceneNode.h"
#include "Light.h"

class LightNode;

typedef std::shared_ptr<LightNode> LightNodePtr;

class LightNode : public ISceneNode
{
public:
	LightNode(ActorPtr pActor) 
	{
		m_pActor = pActor;
	}

	virtual						~LightNode() { }

	virtual void				PreRender()
	{
		return;
	}

	virtual void				Render()
	{
		return;
	}

	virtual const glm::vec3		GetLightColour()
	{
		return GetComponent<Light>()->GetColour();
	}
};

