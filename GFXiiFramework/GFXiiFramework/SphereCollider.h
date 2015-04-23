#pragma once
#include "ICollider.h"
#include "glm\glm.hpp"

class SphereCollider;

typedef std::shared_ptr<SphereCollider> SphereColliderPtr;

class SphereCollider : public ICollider
{
private:
	const std::string			m_type = "sphere";

	glm::vec3					m_centre;
	float						m_radius;

public:
	SphereCollider();
	virtual						~SphereCollider();

	inline virtual void			SetSize(const glm::vec3 centre, const float radius)
	{
		m_centre = centre;
		m_radius = radius;
	}

	inline virtual std::string	GetType() const { return m_type; }

	inline const glm::vec3		GetCentre() const { return m_centre; }
	inline const float			GetRadius() const { return m_radius; }

	virtual void				UpdateCentre(const glm::vec3 position) override { m_centre = position; }

	virtual bool				CollisionDetection(const ColliderPtr pCollider) const override;
};

