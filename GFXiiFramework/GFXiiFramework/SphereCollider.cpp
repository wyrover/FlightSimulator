#include "SphereCollider.h"


SphereCollider::SphereCollider()
{
}


SphereCollider::~SphereCollider()
{
}

bool SphereCollider::CollisionDetection(const ColliderPtr pCollider) const
{
	if (pCollider->GetType() != "sphere")
	{
		return false;
	}

	SphereColliderPtr pSphere = std::tr1::static_pointer_cast<SphereCollider>(pCollider);

	float centres = glm::length(m_centre - pSphere->GetCentre());
	float lengths = m_radius + pSphere->GetRadius();

	if (centres <= lengths)
	{
		return true;
	}

	return false;
}