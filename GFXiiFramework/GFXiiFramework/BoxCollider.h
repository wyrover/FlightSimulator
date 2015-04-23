#pragma once
#include "ICollider.h"

class BoxCollider : public ICollider
{
private:
	const std::string			m_type = "Box";
public:
	BoxCollider();
	virtual						~BoxCollider();

	inline virtual std::string	GetType() const { return m_type; }
};

