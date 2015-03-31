#pragma once
#include "GLM\glm.hpp"
#include "GLM\gtc\quaternion.hpp"
#include "GLM\gtc\matrix_transform.hpp"

class Transform
{
private:
	glm::vec3					m_position;
	glm::vec3					m_upVector;
	glm::vec3					m_rightVector;
	glm::vec3					m_viewVector;

	glm::mat4					m_orientation;
	glm::fquat					m_pitch;
	glm::fquat					m_yaw;
	glm::fquat					m_roll;

public:
	Transform();
	~Transform();

	inline void					SetPosition(glm::vec3 &position)
	{
		m_position = position;
	}

	inline const glm::vec3&		GetPosition() const
	{
		return m_position;
	}

	inline const glm::vec3&		GetUpVector() const
	{
		return m_upVector;
	}

	inline const glm::vec3&		GetRightVector() const
	{
		return m_rightVector;
	}

	inline const glm::vec3&		GetViewVector() const
	{
		return m_viewVector;
	}

	inline const glm::mat4&		GetOrientation() const
	{
		return m_orientation;
	}

	inline void					MoveForward(float amount)
	{
		m_position += (m_viewVector * amount);
	}

	inline void					MoveHorizontal(float amount)
	{
		m_position += (m_rightVector * amount);
	}

	inline void					MoveVertical(float amount)
	{
		m_position += (m_upVector * amount);
	}

	void						Rotation(float yaw, float pitch, float roll);
};

