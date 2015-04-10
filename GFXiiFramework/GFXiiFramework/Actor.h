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
	std::weak_ptr<ComponentType>	GetComponent(ActorComponentID id)
	{
		ActorComponents::iterator iter = m_actorComponents.find(id);

		if (iter != m_actorComponents.end())
		{
			ActorComponentPtr pBase(iter->second);
			std::shared_ptr<ComponentType> pSub(std::tr1::static_pointer_cast<ComponentType>(pBase));
			std::weak_ptr<ComponentType> pWeakSub(pSub);

			return pWeakSub;
		}
		else
		{
			return std::weak_ptr<ComponentType>();
		}
	}

	inline ActorID					GetID() { return m_ID; }

	inline void						AddComponent(ActorComponentPtr pComponent)
	{
		// TODO: Check only one component of each type is attached
		m_actorComponents[pComponent->GetComponentID()] = pComponent;
	}
};
