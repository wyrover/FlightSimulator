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
//#define RADIANS 3.14159265359f / 180.f

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
	//m_position.SetVector(0.0f, 0.0f, 0.0f);
	m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	//m_upVector.SetVector(0.0f, 1.0f, 0.0f);
	m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	//m_direction.SetVector(0.0f, 0.0, -1.0f);
	m_rightVector = glm::cross(m_direction, m_upVector);
	//m_rightVector = m_direction.CrossProduct(m_upVector);
	m_upVector = glm::cross(m_rightVector, m_direction);
	//m_upVector = m_rightVector.CrossProduct(m_direction);
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
	//m_direction.Normalise();

	//Recompute right vector and reinforce orthonormality of this three vectors.
	//Recompute up vector, from new direction and right vector;
	//TODO: Gram-Schmidt orthogonalisation algorithm can be used for this
	m_rightVector = glm::cross(m_direction, m_upVector);
	//m_rightVector = m_direction.CrossProduct(m_upVector);
	m_upVector = glm::cross(m_rightVector, m_direction);
	//m_upVector = m_rightVector.CrossProduct(m_direction);

	glm::normalize(m_rightVector);
	//m_rightVector.Normalise();
	glm::normalize(m_upVector);
	//m_upVector.Normalise();

	UpdateViewMatrix();
}

void Camera::SetUpVector(const glm::vec3* up)
{
	m_upVector = (*up);
	
	m_rightVector = glm::cross(m_direction, m_upVector);
	//m_rightVector = m_direction.CrossProduct(m_upVector);
	m_upVector = glm::cross(m_rightVector, m_direction);
	//m_upVector = m_rightVector.CrossProduct(m_direction);

	glm::normalize(m_rightVector);
	//m_rightVector.Normalise();
	glm::normalize(m_upVector);
	//m_upVector.Normalise();

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	float mat[16];

	mat[0] = m_rightVector[0];
	mat[4] = m_rightVector[1];
	mat[8] = m_rightVector[2];
	
	mat[1] = m_upVector[0];
	mat[5] = m_upVector[1];
	mat[9] = m_upVector[2];

	mat[2] = -m_direction[0];
	mat[6] = -m_direction[1];
	mat[10] = -m_direction[2];

	mat[3] = mat[7] = mat[11] = 0.0f;

	mat[12] = -m_position[0];
	mat[13] = -m_position[1];
	mat[14] = -m_position[2];
	mat[15] = 1.0f;

	//mat[12] = 0.0f;
	//mat[13] = 0.0f;
	//mat[14] = 0.0f;
	//mat[15] = 1.0f;

	m_viewMatrix = glm::make_mat4(mat);


	m_viewMatrix = glm::lookAt(m_position, m_direction, m_upVector);

	std::cout << "Position: " << m_viewMatrix[3][0] << ", " << m_viewMatrix[3][1] << ", " << m_viewMatrix[3][2] << std::endl;
	//std::cout << "Direction: " << mat[2] << ", " << mat[6] << ", " << mat[10] << std::endl;
	std::cout << "Up Vector: " << m_viewMatrix[0][1] << ", " << m_viewMatrix[1][1] << ", " << m_viewMatrix[2][1] << std::endl;
	//std::cout << "Right Vector: " << mat[0] << ", " << mat[4] << ", " << mat[8] << std::endl;
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

// Setup the projection matrix
void Camera::SetProjectionMatrix(float fov, float aspectRatio, float nPlane, float fPlane)
{
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
}

//TODO: Implement the following camera movement
void Camera::StrafeCamera(float amount) 
{
	m_position.x += amount;



	UpdateViewMatrix();
}

void Camera::DollyCamera(float amount) 
{
	m_position.z += amount;

	UpdateViewMatrix();
}
void Camera::PedCamera(float amount) 
{
	m_position.y += amount;

	UpdateViewMatrix();
}

void Camera::RotateCamera(float yaw, float pitch, float roll)
{
	Quaternion quatPitch, quatPitchConj, point;

	point.SetQuaternion(m_rightVector, 0);
	quatPitch.SetQuaternion(m_upVector * (float)sin(TO_RADIANS(pitch / 2.0)), cos(TO_RADIANS(pitch / 2.0)));
	quatPitchConj.SetQuaternion(quatPitch.GetVector() * -1.f, quatPitch.GetScalar());

	m_rightVector = (quatPitch * point * quatPitchConj).GetVector();

	m_direction = glm::cross(m_upVector, m_rightVector);
	UpdateViewMatrix();

	//Quaternion quatPitch, quatPitchConj, point;

	//point.SetQuaternion(m_upVector, 0);
	//quatPitch.SetQuaternion(m_rightVector * (float)sin(TO_RADIANS(pitch) / 2.0), cos(TO_RADIANS(pitch / 2.0)));
	//quatPitchConj.SetQuaternion(quatPitch.GetVector() * -1.f, quatPitch.GetScalar());

	//m_upVector = (quatPitch * point * quatPitchConj).GetVector();

	//m_direction = glm::cross(m_upVector, m_rightVector);
	//UpdateViewMatrix();
}

void Camera::ZoomCamera(float amount) {}