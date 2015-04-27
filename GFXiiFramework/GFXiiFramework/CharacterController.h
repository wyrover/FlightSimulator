#pragma once
#include "ActorComponent.h"
#include "Input.h"
#include <vector>
#include "Rigidbody.h"
#include "Actor.h"

class CharacterController;

typedef std::shared_ptr<CharacterController> CharacterControllerPtr;
typedef std::vector<ActorPtr> ActorList;

class CharacterController : public ActorComponent
{
private:
	ActorPtr							m_pProjectilePrefab;
	unsigned							m_tick;

	ActorList							m_projectiles;

public:
	CharacterController();
	virtual								~CharacterController();

	static const ActorComponentID		COMPONENT_ID = 7;

	inline virtual ActorComponentID		GetComponentID() const override
	{
		return COMPONENT_ID;
	}

	inline void							SetProjectilePrefab(const ActorPtr pActor)
	{
		m_pProjectilePrefab = pActor;
	}

	ActorPtr							UpdateProjectiles();

	inline ActorList&					GetProjectilesList()
	{
		return m_projectiles;
	}

	void								RemoveProjectile(const ActorPtr pActor);

	ActorPtr							Update();
};

