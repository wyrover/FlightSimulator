#pragma once
#include <vector>
#include "Actor.h"

/*
	ISceneNode is an interface class that all scene nodes will inherit from
*/

class ISceneNode;

typedef std::shared_ptr<ISceneNode> SceneNodePtr;
typedef std::vector<SceneNodePtr> SceneNodeList;
typedef std::weak_ptr<Actor> WeakActorPtr;

class ISceneNode
{
protected:
	ActorPtr									m_pActor;

	ISceneNode									*m_pParent;
	SceneNodeList								m_children;

	// Used to set whether a node should be rendered/used in the scene
	bool										m_visible;

public:
	ISceneNode() { }
	virtual										~ISceneNode() { }

	// NOTE: The node should render itself, then each of its children
	virtual void								Render() = 0;

	inline virtual void							AddChild(const SceneNodePtr pNode)
	{
		pNode->m_pParent = this;

		m_children.push_back(pNode);
	}

	template <class ComponentType>
	inline std::shared_ptr<ComponentType>		GetComponent()
	{
		return m_pActor->GetComponent<ComponentType>();
	}

	virtual void								PreRender() = 0;
};

