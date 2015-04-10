#pragma once
#include <map>
#include <memory>
#include "ActorComponent.h"

typedef unsigned int ActorID;

class ActorComponent;

typedef std::map<ActorComponent, std::shared_ptr<ActorComponent>> ActorComponents;

class Actor
{
private:
public:
	Actor() { }
	virtual ~Actor() { }
};