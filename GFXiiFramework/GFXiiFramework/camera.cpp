//Created for Graphics I and II
//Author: Minsi Chen

#include <Windows.h>
#include <gl\GL.h>
#include "camera.h"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtx\quaternion.hpp"
#include "glm\gtc\matrix_transform.hpp"

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
	glm::vec3 zaxis = glm::normalize(m_position - (m_position + m_direction));
	glm::vec3 xaxis = glm::normalize(glm::cross(m_upVector, zaxis));
	glm::vec3 yaxis = glm::cross(zaxis, xaxis);

	// view matrix... ??
	m_viewMatrix = {
		glm::vec4(xaxis.x, yaxis.x, zaxis.x, 0),
		glm::vec4(xaxis.y, yaxis.y, zaxis.y, 0),
		glm::vec4(xaxis.z, yaxis.z, zaxis.z, 0),
		glm::vec4(-glm::dot(xaxis, m_position), -glm::dot(yaxis, m_position), -glm::dot(zaxis, m_position), 1)
	};

	// Debug
	std::cout << "========== camera.cpp ==========" << std::endl;
	std::cout << m_viewMatrix[0][0] << " " << m_viewMatrix[0][1] << " " << m_viewMatrix[0][2] << " " << m_viewMatrix[0][3] << "\n"
		<< m_viewMatrix[1][0] << " " << m_viewMatrix[1][1] << " " << m_viewMatrix[1][2] << " " << m_viewMatrix[1][3] << "\n"
		<< m_viewMatrix[2][0] << " " << m_viewMatrix[2][1] << " " << m_viewMatrix[2][2] << " " << m_viewMatrix[2][3] << "\n"
		<< m_viewMatrix[3][0] << " " << m_viewMatrix[3][1] << " " << m_viewMatrix[3][2] << " " << m_viewMatrix[3][3] << std::endl;
}

void Camera::GetModelView(float mat[16])
{
	for (unsigned row = 0; row < 4; row++)
	{
		for (unsigned column = 0; column < 4; column++)
		{
			*mat = m_viewMatrix[row][column];
			mat++;
		}
	}
}

void Camera::GetProjection(float mat[16])
{
	mat[0] = m_projectionMatrix[0][0];
	mat[2] = m_projectionMatrix[0][2];
	mat[5] = m_projectionMatrix[1][1];
	mat[6] = m_projectionMatrix[1][2];
	mat[10] = m_projectionMatrix[2][2];
	mat[11] = m_projectionMatrix[2][3];
	mat[14] = m_projectionMatrix[3][2];
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
	m_position -= (m_direction * amount);

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
	glm::fquat pitchQuat(cos(TO_RADIANS(pitch / 2.0)), m_rightVector * (float)sin(TO_RADIANS(pitch / 2.0)));
	glm::fquat yawQuat(cos(TO_RADIANS(yaw / 2.0)), m_upVector * (float)sin(TO_RADIANS(yaw / 2.0)));
	glm::fquat rollQuat(cos(TO_RADIANS(roll / 2.0)), m_direction * (float)sin(TO_RADIANS(roll / 2.0)));
	glm::fquat rotation = pitchQuat * yawQuat * rollQuat;

	m_direction = rotation * m_direction * glm::conjugate(rotation);
	m_rightVector = rotation * m_rightVector * glm::conjugate(rotation);
	m_upVector = rotation * m_upVector * glm::conjugate(rotation);

	UpdateViewMatrix();
}

void Camera::ZoomCamera(float amount)
{
	// ! May want to change this
	if ((m_fov + amount) < 100.f && (m_fov + amount) > 25.f)
		SetProjectionMatrix(m_fov + amount, m_aspectRatio, m_nPlane, m_fPlane);
}

void Camera::MouseDown()
{
	m_mouseDown = true;
}

void Camera::MouseUp()
{
	m_mouseDown = false;
}

void Camera::MouseMove(int x, int y)
{
	if (m_mouseDown)
	{
		RotateCamera((m_lastX - x) / 5.0, (m_lastY - y), 0);
	}

	// Update mouse positions
	m_lastX = x;
	m_lastY = y;
}