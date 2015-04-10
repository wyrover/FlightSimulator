#pragma once
#include "Actor.h"

typedef unsigned int ActorComponentID;

class ActorComponent
{
protected:
	std::shared_ptr<Actor>						m_pOwner;

public:
	ActorComponent() { }
	virtual ~ActorComponent() { }

	inline void							SetOwner(std::shared_ptr<Actor> owner) { m_pOwner = owner; }
};