#pragma once
#include <map>
#include <memory>
#include "Transform.h"
#include "TransformComponent.h"

class ActorComponent;

typedef unsigned int ActorID, ActorComponentID;
typedef std::shared_ptr<ActorComponent> ActorComponentPtr;
typedef std::map<ActorComponentID, ActorComponentPtr> ActorComponents;

class Actor : public Transform
{
	friend class ActorFactory;

private:
	ActorID							m_ID;
	ActorComponents					m_actorComponents;

public:
	Actor(){ }
	virtual ~Actor() { }

	inline ActorID					GetID() { return m_ID; }

	inline void						AddComponent(ActorComponentPtr pComponent)
	{
		// TODO: Check only one component of each type is attached
		m_actorComponents[pComponent->GetComponentID()] = pComponent;
	}

	template <class ComponentType>
	std::weak_ptr<ComponentType>	GetComponent(ActorComponentID id);
};
