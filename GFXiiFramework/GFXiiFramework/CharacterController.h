#pragma once
#include "ActorComponent.h"
#include "Input.h"

class CharacterController;

typedef std::shared_ptr<CharacterController> CharacterControllerPtr;

class CharacterController : public ActorComponent
{
public:
	CharacterController();
	virtual								~CharacterController();

	static const ActorComponentID		COMPONENT_ID = 7;

	inline virtual ActorComponentID		GetComponentID() const override
	{
		return COMPONENT_ID;
	}

	void								Update();
};

