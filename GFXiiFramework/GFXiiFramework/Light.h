#pragma once
#include "ActorComponent.h"
#include "glm\vec3.hpp"

class Light;

typedef std::shared_ptr<Light> LightPtr;

class Light : public ActorComponent
{
protected:
	glm::vec3							m_colour;

public:
	Light() { }
	virtual								~Light() { }

	static const ActorComponentID		COMPONENT_ID = 6;

	inline virtual ActorComponentID		GetComponentID() const  override
	{
		return COMPONENT_ID;
	}

	inline void							SetColour(const glm::vec3 colour)
	{
		m_colour = colour;
	}

	inline const glm::vec3&				GetColour() const
	{
		return m_colour;
	}
};

