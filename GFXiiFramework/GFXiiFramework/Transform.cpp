#include "Transform.h"
#include <iostream>

Transform::Transform()
{
	// Set all objects to default at the centre and face away from the screen
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	m_viewVector = glm::vec3(0.0f, 0.0f, -1.f);

	m_rightVector = glm::cross(m_viewVector, m_upVector);
	m_upVector = glm::cross(m_rightVector, m_viewVector);
}

Transform::~Transform()
{
}

void Transform::Rotation(float yaw, float pitch, float roll)
{
	// Fuck quaternions
	m_pitch = glm::fquat(cos(glm::radians(pitch / 2.0f)), m_rightVector * (float)sin(glm::radians(pitch / 2.0f)));
	m_yaw = glm::fquat(cos(glm::radians(yaw / 2.0f)), m_upVector * (float)sin(glm::radians(yaw / 2.0f)));
	m_roll = glm::fquat(cos(glm::radians(roll / 2.0f)), m_viewVector * (float)sin(glm::radians(roll / 2.0f)));

	m_orientation = glm::mat4(m_pitch * m_yaw * m_roll);

	glm::vec4 view = glm::vec4(m_viewVector, 0);
	glm::vec4 up = glm::vec4(m_upVector, 0);
	glm::vec4 right = glm::vec4(m_rightVector, 0);

	m_viewVector = glm::normalize(glm::vec3(m_orientation * view));
	m_upVector = glm::normalize(glm::vec3(m_orientation * up));
	m_rightVector = glm::normalize(glm::vec3(m_orientation * right));

	m_viewVector = glm::normalize(glm::cross(m_upVector, m_rightVector));
	m_upVector = glm::normalize(glm::cross(m_rightVector, m_viewVector));
	m_rightVector = glm::normalize(glm::cross(m_viewVector, m_upVector));
}