//Created for Graphics I and II
//Author: Minsi Chen

#include "OGLCamera.h"
#include "..\GLM\gtc\quaternion.hpp"
#include "..\GLM\gtc\matrix_transform.hpp"
#include "..\Input.h"

OGLCamera::OGLCamera()
{
	InitCamera();
}

OGLCamera::~OGLCamera()
{
}

void OGLCamera::InitCamera()
{
	//Initialise the OGLCamera that sits at the origin looking down the negative z-axis.
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	m_viewVector = glm::vec3(0.0f, 0.0f, -1.f);

	m_rightVector = glm::cross(m_viewVector, m_upVector);
	m_upVector = glm::cross(m_rightVector, m_viewVector);

	UpdateViewMatrix();
}

void OGLCamera::SetCameraPosition(const glm::vec3 &position)
{
	m_position = position;
	UpdateViewMatrix();
}

void OGLCamera::SetLookAtPoint(const glm::vec3 &lookAt)
{
	m_viewVector = lookAt - m_position;
	m_viewVector = glm::normalize(m_viewVector);
	
	//Recompute right vector and reinforce orthonormality of this three vectors.
	//Recompute up vector, from new direction and right vector;
	//TODO: Gram-Schmidt orthogonalisation algorithm can be used for this

	m_rightVector = glm::cross(m_viewVector, m_upVector);
	m_upVector = glm::cross(m_rightVector, m_viewVector);

	UpdateViewMatrix();
}

void OGLCamera::SetUpVector(const glm::vec3 &up)
{
	m_upVector = up;
	
	m_rightVector = glm::cross(m_viewVector, m_upVector);
	m_upVector = glm::cross(m_rightVector, m_viewVector);

	m_rightVector = glm::normalize(m_rightVector);
	m_upVector = glm::normalize(m_upVector);

	UpdateViewMatrix();
}

void OGLCamera::UpdateViewMatrix()
{
	// Reset the view
	m_viewMatrix = glm::lookAt(m_position, m_position + m_viewVector, m_upVector);
}

void OGLCamera::RotateCamera(float yaw, float pitch, float roll)
{
	// Fuck quaternions
	glm::fquat pitchQuat(cos(glm::radians(pitch / 2.0f)), m_rightVector * (float)sin(glm::radians(pitch / 2.0f)));
	glm::fquat yawQuat(cos(glm::radians(yaw / 2.0f)), m_upVector * (float)sin(glm::radians(yaw / 2.0f)));
	glm::fquat rollQuat(cos(glm::radians(roll / 2.0f)), m_viewVector * (float)sin(glm::radians(roll / 2.0f)));

	glm::mat4 rotation = glm::mat4(pitchQuat * yawQuat * rollQuat);

	glm::vec4 direction = glm::vec4(m_viewVector.x, m_viewVector.y, m_viewVector.z, 0);
	glm::vec4 up = glm::vec4(m_upVector.x, m_upVector.y, m_upVector.z, 0);
	glm::vec4 right = glm::vec4(m_rightVector.x, m_rightVector.y, m_rightVector.z, 0);

	m_viewVector = glm::normalize(glm::vec3(rotation * direction));
	m_upVector = glm::normalize(glm::vec3(rotation * up));
	m_rightVector = glm::normalize(glm::vec3(rotation * right));

	m_viewVector = glm::normalize(glm::cross(m_upVector, m_rightVector));
	m_upVector = glm::normalize(glm::cross(m_rightVector, m_viewVector));
	m_rightVector = glm::normalize(glm::cross(m_viewVector, m_upVector));

	UpdateViewMatrix();
}

void OGLCamera::Update()
{
	RotateCamera(Input::Get().Yaw(), Input::Get().Pitch(), Input::Get().Roll());
	
	DollyCamera(Input::Get().Forward());
	StrafeCamera(Input::Get().Horizontal());
	PedCamera(Input::Get().Vertical());
}

void OGLCamera::StrafeCamera(float amount)
{
	m_position += (m_rightVector * amount);

	UpdateViewMatrix();
}

void OGLCamera::DollyCamera(float amount)
{
	m_position += (m_viewVector * amount);

	UpdateViewMatrix();
}

void OGLCamera::PedCamera(float amount)
{
	m_position += (m_upVector * amount);

	UpdateViewMatrix();
}