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

	inline virtual ActorComponentID				GetComponentID() = 0;
};