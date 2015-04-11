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

	inline virtual ActorComponentID				GetComponentID() const = 0;
};