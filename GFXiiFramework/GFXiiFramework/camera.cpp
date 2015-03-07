//Created for Graphics I and II
//Author: Minsi Chen

#include <Windows.h>
#include <gl\GL.h>
#include "camera.h"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\quaternion.hpp"

#define RADIANS 3.14159265359 / 180.0

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

	m_viewMatrix = glm::make_mat4(mat);
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

	float n = nPlane;
	float f = fPlane;

	float t = tan(fov * 3.14159 / 360.0) * nPlane;
	float b = -t;

	float r = aspectRatio * t;
	float l = aspectRatio * b;

	m_projectionMatrix[0][0] = (2 * n) / (r - l);
	m_projectionMatrix[0][2] = (r + l) / (r - l);
	m_projectionMatrix[1][1] = (2 * n) / (t - b);
	m_projectionMatrix[1][2] = (t + b) / (t - b);
	m_projectionMatrix[2][2] = (n + f) / (n - f);
	m_projectionMatrix[2][3] = (2 * f * n) / (n - f);
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
	glm::mat4 rotX, rotY, rotZ;

	SetRotationY(rotY, pitch);

	float tempX = m_viewMatrix[0][3];
	float tempY = m_viewMatrix[1][3];
	float tempZ = m_viewMatrix[2][3];

	m_viewMatrix[0][3] = m_viewMatrix[1][3] = m_viewMatrix[2][3] = 0;
	m_viewMatrix *= rotY;

	m_viewMatrix[0][3] = tempX;
	m_viewMatrix[1][3] = tempY;
	m_viewMatrix[2][3] = tempZ;
}

void Camera::ZoomCamera(float amount) {}

void Camera::SetRotationY(glm::mat4 &mat, float &rot)
{
	mat = glm::mat4();

	mat[0][0] = cos(rot * RADIANS);
	mat[0][2] = sin(rot * RADIANS);
	mat[2][0] = -sin(rot * RADIANS);
	mat[2][2] = cos(rot * RADIANS);
}