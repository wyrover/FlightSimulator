#include "Rigidbody.h"
#include "Transform.h"
#include "Actor.h"

Rigidbody::Rigidbody()
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update()
{
	m_pCollider->UpdateCentre(GetComponent<Transform>()->GetPosition());
}