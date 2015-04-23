#pragma once
#include <memory>
#include <string>
#include "glm\glm.hpp"

class ICollider;

typedef std::shared_ptr<ICollider> ColliderPtr;

class ICollider
{
public:
	ICollider() { }
	virtual							~ICollider() { }

	virtual bool					CollisionDetection(const ColliderPtr pCollider) const  = 0;
	inline virtual std::string		GetType() const = 0;

	virtual void					UpdateCentre(const glm::vec3 position) = 0;
};

