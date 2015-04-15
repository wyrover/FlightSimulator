#pragma once
#include <map>
#include <memory>

class Actor;

typedef unsigned int ActorComponentID;
typedef std::shared_ptr<Actor> ActorPtr;

class ActorComponent
{
protected:
	ActorPtr									m_pOwner;

public:
	ActorComponent() { }
	virtual ~ActorComponent() { }

	inline void									SetOwner(ActorPtr owner) { m_pOwner = owner; }

	inline const ActorPtr						GetOwner() const
	{
		return m_pOwner;
	}

	template <class ComponentType>
	inline std::shared_ptr<ComponentType>		GetComponent()
	{
		return m_pOwner->GetComponent<ComponentType>();
	}

	inline virtual ActorComponentID				GetComponentID() const = 0;
};