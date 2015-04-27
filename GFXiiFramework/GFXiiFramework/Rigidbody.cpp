#include "Rigidbody.h"
#include "Transform.h"
#include "Actor.h"

Rigidbody::Rigidbody()
{
	m_tick = 0;
}

Rigidbody::~Rigidbody()
{
}

bool Rigidbody::Update()
{
	m_pCollider->UpdateCentre(GetComponent<Transform>()->GetPosition());

	if (!m_timerSet)
		return false;

	m_tick++;

	if (m_tick > 60)
		return true;
	return false;
}