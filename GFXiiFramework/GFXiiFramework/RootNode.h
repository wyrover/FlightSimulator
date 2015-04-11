#pragma once
#include "ISceneNode.h"

class RootNode : public ISceneNode
{
public:

									RootNode() { }
	virtual							~RootNode() { }

	void							Render() const
	{
		for (const SceneNodePtr &pSceneNode : m_children)
		{
			pSceneNode->Render();
		}
	}
};

