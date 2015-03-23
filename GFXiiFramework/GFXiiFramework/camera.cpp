//Created for Graphics I and II
//Author: Minsi Chen

#include <Windows.h>
#include <gl\GL.h>
#include "camera.h"
#include "Input.h"

#include <iostream>

#define TO_RADIANS(x) (x * 3.14159265359 / 180.0)

Camera::Camera()
{
	InitCamera();
}

Camera::~Camera()
{
}

void Camera::InitCamera()
{
	//Initialise the camera that sits at the origin looking down the negative z-axis.

	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	m_direction = glm::vec3(0.0f, 0.0f, -1.0f);

	m_rightVector = glm::cross(m_direction, m_upVector);
	m_upVector = glm::cross(m_rightVector, m_direction);

	UpdateViewMatrix();
}

void Camera::SetCameraPosition(const glm::vec3* position)
{
	m_position = (*position);
	UpdateViewMatrix();
}

void Camera::SetLookAtPoint(const glm::vec3* lookAt)
{
	m_direction = glm::normalize((*lookAt) - m_position);

	//Recompute right vector and reinforce orthonormality of this three vectors.
	//Recompute up vector, from new direction and right vector;
	//TODO: Gram-Schmidt orthogonalisation algorithm can be used for this

	m_rightVector = glm::cross(m_direction, m_upVector);
	m_upVector = glm::cross(m_rightVector, m_direction);

	glm::normalize(m_rightVector);
	glm::normalize(m_upVector);

	UpdateViewMatrix();
}

void Camera::SetUpVector(const glm::vec3* up)
{
	m_upVector = (*up);
	
	m_rightVector = glm::cross(m_direction, m_upVector);
	m_upVector = glm::cross(m_rightVector, m_direction);

	glm::normalize(m_rightVector);
	glm::normalize(m_upVector);

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_upVector);
}

void Camera::SetProjectionMatrix(float fov, float aspectRatio, float nPlane, float fPlane)
{
	// Set up
	m_projectionMatrix = glm::mat4();

	float t = tan(fov * 3.14159 / 360.0) * nPlane;

	float r = aspectRatio * t;
	float l = aspectRatio * -t;

	m_projectionMatrix[0][0] = (2 * nPlane) / (r - l);
	m_projectionMatrix[0][2] = (r + l) / (r - l);
	m_projectionMatrix[1][1] = (2 * nPlane) / (t + t);
	m_projectionMatrix[1][2] = (t - t) / (t + t);
	m_projectionMatrix[2][2] = (nPlane + fPlane) / (nPlane - fPlane);
	m_projectionMatrix[2][3] = (2 * fPlane * nPlane) / (nPlane - fPlane);
	m_projectionMatrix[3][2] = -1;

	// store values
	m_fov = fov;
	m_aspectRatio = aspectRatio;
	m_nPlane = nPlane;
	m_fPlane = fPlane;
}

void Camera::StrafeCamera(float amount) 
{
	m_position += (m_rightVector * amount);

	UpdateViewMatrix();
}

void Camera::DollyCamera(float amount) 
{
	m_position += (m_direction * amount);

	UpdateViewMatrix();
}
void Camera::PedCamera(float amount) 
{
	m_position += (m_upVector * amount);

	UpdateViewMatrix();
}

void Camera::RotateCamera(float yaw, float pitch, float roll)
{
	// Fuck quaternions
	glm::fquat pitchQuat(cos(TO_RADIANS(pitch / 2.0f)), glm::cross(m_direction, glm::vec3(0, 1, 0)) * (float)sin(TO_RADIANS(pitch / 2.0f)));
	glm::fquat yawQuat(cos(TO_RADIANS(yaw / 2.0f)), glm::vec3(0, 1, 0) * (float)sin(TO_RADIANS(yaw / 2.0f)));
	glm::fquat rollQuat(cos(TO_RADIANS(roll / 2.0f)), m_direction * (float)sin(TO_RADIANS(roll / 2.0f)));
	
	//float result = abs(glm::dot(m_direction, glm::vec3(0, 1, 0)) - 1);

	//std::cout << result << std::endl;

	//if (result > 0.1f)
	//	m_rotation = yawQuat * pitchQuat * rollQuat;
	//else
	//	m_rotation = yawQuat * rollQuat;

	m_rotation = yawQuat * pitchQuat * rollQuat;

	m_direction = glm::normalize(m_rotation * m_direction * glm::conjugate(m_rotation));
	m_upVector = glm::normalize(m_rotation * m_upVector * glm::conjugate(m_rotation));
	m_rightVector = glm::normalize(m_rotation * m_rightVector * glm::conjugate(m_rotation));

	m_direction = glm::normalize(glm::cross(m_upVector, m_rightVector));
	m_upVector = glm::normalize(glm::cross(m_rightVector, m_direction));
	m_rightVector = glm::normalize(glm::cross(m_direction, m_upVector));

	UpdateViewMatrix();
}

void Camera::ZoomCamera(float amount)
{
	// ! May want to change this
	if ((m_fov + amount) < 100.f && (m_fov + amount) > 25.f)
		SetProjectionMatrix(m_fov + amount, m_aspectRatio, m_nPlane, m_fPlane);
}

void Camera::Update()
{
	StrafeCamera(Input::Get().Horizontal());
	PedCamera(Input::Get().Vertical());
	DollyCamera(Input::Get().Forward());
	ZoomCamera(Input::Get().GetZoom());

	RotateCamera(Input::Get().Yaw(), Input::Get().Pitch(), Input::Get().Roll());
}