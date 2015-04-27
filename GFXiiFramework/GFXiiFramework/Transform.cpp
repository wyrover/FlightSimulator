#include "Transform.h"

Transform::Transform()
{
	// Set all objects to default at the centre and face away from the screen
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_upVector = glm::vec3(0.0f, 0.0f, 0.0f);
	m_viewVector = glm::vec3(0.0f, 0.0f, 0.0f);

	m_yaw = m_pitch = m_roll = 0.0f;
}

Transform::~Transform()
{
}

void Transform::Rotation(float yaw, float pitch, float roll)
{
	m_yaw += yaw;
	m_pitch += pitch;
	m_roll += roll;

	// Fuck quaternions
	glm::fquat pitchQuat(cos(glm::radians(pitch / 2.0f)), m_rightVector * (float)sin(glm::radians(pitch / 2.0f)));
	glm::fquat yawQuat(cos(glm::radians(yaw / 2.0f)), m_upVector * (float)sin(glm::radians(yaw / 2.0f)));
	glm::fquat rollQuat(cos(glm::radians(roll / 2.0f)), m_viewVector * (float)sin(glm::radians(roll / 2.0f)));

	glm::mat4 rotation(yawQuat * pitchQuat * rollQuat);

	m_viewVector = glm::normalize(glm::vec3(rotation * glm::vec4(m_viewVector, 0.0f)));
	m_upVector = glm::normalize(glm::vec3(rotation * glm::vec4(m_upVector, 0.0f)));
	m_rightVector = glm::normalize(glm::vec3(rotation * glm::vec4(m_rightVector, 0.0f)));

	m_viewVector = glm::normalize(glm::cross(m_upVector, m_rightVector));
	m_upVector = glm::normalize(glm::cross(m_rightVector, m_viewVector));
	m_rightVector = glm::normalize(glm::cross(m_viewVector, m_upVector));

	m_orientation = rotation * m_orientation;
}