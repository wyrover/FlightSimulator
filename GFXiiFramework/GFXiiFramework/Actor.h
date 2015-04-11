#pragma once
#include <map>
#include <memory>
#include "ActorComponent.h"

class ActorComponent;

typedef unsigned int ActorID, ActorComponentID;

typedef std::shared_ptr<ActorComponent> ActorComponentPtr;
typedef std::map<ActorComponentID, ActorComponentPtr> ActorComponents;

class Actor
{
	friend class ActorFactory;

private:
	ActorID							m_ID;
	ActorComponents					m_actorComponents;

public:
	Actor(){ }
	virtual ~Actor() { }

	template <class ComponentType>
	std::shared_ptr<ComponentType>	GetComponent()
	{
		ActorComponentPtr pActorComponent = std::make_shared<ComponentType>();

		ActorComponents::iterator iter = m_actorComponents.find(pActorComponent->GetComponentID());
		
		if (iter != m_actorComponents.end())
		{
			return std::shared_ptr<ComponentType>(std::tr1::static_pointer_cast<ComponentType>(iter->second));
		}
		else
		{
			return std::shared_ptr<ComponentType>();
		}
	}

	inline ActorID					GetID() { return m_ID; }

	inline void						AddComponent(ActorComponentPtr pComponent)
	{
		// TODO: Check only one component of each type is attached
		m_actorComponents[pComponent->GetComponentID()] = pComponent;
	}
};
