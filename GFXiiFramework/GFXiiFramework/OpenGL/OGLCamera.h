//Created for Graphics I and II
//Author: Minsi Chen

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "..\Actor.h"
#include "..\GLM\gtc\matrix_transform.hpp"

class OGLCamera : public Actor
{
	public:
		enum ECameraType
		{
			CAM_ORTHOGRAPHIC,
			CAM_PERSPECTIVE
		};

	private:
		glm::mat4						m_viewMatrix;
		glm::mat4						m_projectionMatrix;
		ECameraType						m_cameratype;
		float							m_fov;
		float							m_aspectRatio;
		float							m_width;
		float							m_height;
		float							m_near;
		float							m_far;

	public:
	
										OGLCamera() { ; }
		virtual							~OGLCamera() { ; }

		inline void						UpdateViewMatrix()
		{
			//m_viewMatrix = glm::lookAt(GetPosition(), GetPosition() + GetViewVector(), GetUpVector());
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

		inline const glm::mat4&			GetViewMatrixMat4() const
		{
			return m_viewMatrix;
		}

		inline const glm::mat4&			GetProjectionMat4() const
		{
			return m_projectionMatrix;
		}

		inline void							SetProjection(float fov, float width, float height, float nPlane, float fPlane)
		{
			m_projectionMatrix = glm::perspectiveFov(glm::radians(fov), width, height, nPlane, fPlane);

			m_fov = fov;
			m_aspectRatio = width / height;
			m_width = width;
			m_height = height;
			m_near = nPlane;
			m_far = fPlane;
		}

		void							Update();
		void							ZoomCamera(float amount);
};

#endif
