#pragma once
#include "ActorComponent.h"
#include "ICollider.h"
#include <vector>

class Rigidbody;

typedef std::shared_ptr<Rigidbody> RigidbodyPtr;
typedef std::vector<RigidbodyPtr> RigidbodyList;

class Rigidbody : public ActorComponent
{
private:
	ColliderPtr								m_pCollider;

	// Just for the projectiles
	bool									m_timerSet;
	int										m_tick;

public:
	Rigidbody();
	virtual									~Rigidbody();

	static const ActorComponentID			COMPONENT_ID = 8;

	inline virtual ActorComponentID			GetComponentID() const override { return COMPONENT_ID; }
	inline virtual void						SetCollider(ColliderPtr pCollider) { m_pCollider = pCollider; }

	inline const ColliderPtr				GetCollider() const { return m_pCollider; }

	inline void								SetTimer(bool setTimer)
	{
		m_timerSet = setTimer;
	}

	virtual bool							Update();
};