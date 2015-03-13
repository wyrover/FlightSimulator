//Created for Graphics I and II
//Author: Minsi Chen

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "glm\glm.hpp"
#include "quaternion.h"

class Camera
{
	public:
		enum ECameraType
		{
			CAM_ORTHOGRAPHIC,
			CAM_PERSPECTIVE
		};

	private:
		glm::mat4						m_viewMatrix;				//View Matrix
		glm::mat4						m_projectionMatrix;			//Projection Matrix
		glm::vec3						m_position;					//Position
		glm::vec3						m_upVector;					//up vector
		glm::vec3						m_rightVector;				//right vector
		glm::vec3						m_viewVector;				//view vector
		glm::vec3						m_lookAt;					//look at position
		glm::vec3						m_direction;
		ECameraType						m_cameratype;				//Projection time
		float							m_fov;						//vertical field of view in degree
		float							m_aspectRatio;

		glm::mat4 m_rotX, m_rotY, m_rotZ;
		float rotAmount;
		
	public:
	
										Camera();
		virtual							~Camera();

		void							InitCamera();
		void							SetCameraPosition(const glm::vec3* position);
		inline const glm::vec3*			GetCameraPosition() const 
		{
			return &m_position;
		}

		void							SetLookAtPoint(const glm::vec3* lookAt);
		inline const glm::vec3*			GetCameraDirection() const
		{
			return &m_direction;
		}
		void							SetUpVector(const glm::vec3* up);
		inline const glm::vec3*			GetCameraUpVector() const
		{
			return &m_upVector;
		}
		inline ECameraType				GetCameraType()
		{
			return m_cameratype;
		}

		inline void						SetCameraFOV(float fov)
		{
			m_fov = fov;
		}

		inline float					GetCameraFOV()
		{
			return m_fov;
		}

		inline void						SetCameraAspectRatio(float ar)
		{
			m_aspectRatio = ar;
		}

		inline float					GetCameraAspectRatio()
		{
			return m_aspectRatio;
		}

		void							UpdateViewMatrix();

		inline const glm::mat4*			GetViewMatrix() const
		{
			return &m_viewMatrix;
		}

		inline const glm::mat4*			GetProjectionMatrix() const
		{
			return &m_projectionMatrix;
		}
	
		//TODO: Setup the projection matrix
		void							SetProjectionMatrix(float fov, float aspectRatio, float nPlane, float fPlane);

		//TODO: Implement the following camera movement
		void							StrafeCamera(float amount);
		void							DollyCamera(float amount);
		void							PedCamera(float amount);
		void							RotateCamera(float yaw, float pitch, float roll);
		void							ZoomCamera(float amount);

		void							GetModelView(float mat[16]);
		void							GetProjection(float mat[16]);
};

#endif
