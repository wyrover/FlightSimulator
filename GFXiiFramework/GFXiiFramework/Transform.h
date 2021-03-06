#pragma once
#include "ActorComponent.h"
#include "GLM\glm.hpp"
#include "GLM\gtc\quaternion.hpp"
#include "GLM\gtc\matrix_transform.hpp"

class Transform;

typedef std::shared_ptr<Transform> TransformPtr;

class Transform : public ActorComponent
{
private:

	glm::vec3							m_position;
	glm::vec3							m_upVector;
	glm::vec3							m_rightVector;
	glm::vec3							m_viewVector;

	glm::mat4							m_orientation;
	float								m_pitch;
	float								m_yaw;
	float								m_roll;

	glm::mat4							m_scale;

public:
	Transform();
	virtual ~Transform();

#pragma region INLINES

	static const ActorComponentID		COMPONENT_ID = 1;

	inline virtual ActorComponentID		GetComponentID() const override 
	{ 
		return COMPONENT_ID;
	}

	inline void							SetPosition(glm::vec3 position)
	{
		m_position = position;
	}

	inline void							SetUniformScale(float scale)
	{
		m_scale = glm::scale(glm::mat4(), glm::vec3(scale, scale, scale));
	}

	inline void							SetScale(float x, float y, float z)
	{
		m_scale = glm::scale(glm::mat4(), glm::vec3(x, y, z));
	}

	inline const glm::mat4				GetScale() const
	{
		return m_scale;
	}

	inline glm::mat4					GetTransformation()
	{
		return glm::translate(glm::mat4(), m_position) * m_scale * m_orientation;
	}

	inline const glm::vec3				GetPosition() const
	{
		return m_position;
	}

	inline const glm::vec3				GetUpVector() const
	{
		return m_upVector;
	}

	inline const glm::vec3				GetRightVector() const
	{
		return m_rightVector;
	}

	inline const glm::vec3				GetViewVector() const
	{
		return m_viewVector;
	}

	inline const glm::mat4				GetOrientation() const
	{
		return m_orientation;
	}

	inline void							SetOrientation(const glm::mat4 &orientation)
	{
		m_orientation = orientation;

		m_upVector = glm::vec3(orientation * glm::vec4(m_upVector, 0));
		m_viewVector = glm::vec3(orientation * glm::vec4(m_viewVector, 0));
		m_rightVector = glm::vec3(orientation * glm::vec4(m_rightVector, 0));
	}

	inline void							MoveForward(float amount)
	{
		m_position += (m_viewVector * amount);
	}

	inline void							MoveHorizontal(float amount)
	{
		m_position += (m_rightVector * amount);
	}

	inline void							MoveVertical(float amount)
	{
		m_position += (m_upVector * amount);
	}

	inline void							Set(glm::vec3 up, glm::vec3 right, glm::vec3 view, glm::vec3 position)
	{
		m_upVector = up;
		m_rightVector = right;
		m_viewVector = view;
		m_position = position;
	}

	inline void							SetUp(const glm::vec3 up)
	{
		m_upVector = up;
	}

	inline void							SetRight(const glm::vec3 right)
	{
		m_rightVector = right;
	}

	inline void							SetView(const glm::vec3 view)
	{
		m_viewVector = view;
	}

#pragma endregion INLINES

	inline float						GetYaw() const { return m_yaw; }
	inline float						GetPitch() const { return m_pitch; }
	inline float						GetRoll() const { return m_roll; }

	void								Rotation(float yaw, float pitch, float roll);
};

