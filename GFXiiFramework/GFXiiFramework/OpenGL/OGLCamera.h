//Created for Graphics I and II
//Author: Minsi Chen

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "..\GLM\glm.hpp"
#include "..\GLM\gtc\matrix_transform.hpp"

class OGLCamera
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
		ECameraType						m_cameratype;				//Projection time
		float							m_fov;						//vertical field of view in degree
		float							m_aspectRatio;
		float							m_width;
		float							m_height;
		float							m_near;
		float							m_far;

		glm::mat4						m_rotation;

	public:
	
										OGLCamera();
		virtual							~OGLCamera();

		void							InitCamera();
		void							SetCameraPosition(const glm::vec3 &position);
		inline const glm::vec3&			GetCameraPosition() const 
		{
			return m_position;
		}

		void							SetLookAtPoint(const glm::vec3 &lookAt);
		inline const glm::vec3&			GetCameraDirection() const
		{
			return m_viewVector;
		}
		void							SetUpVector(const glm::vec3 &up);
		inline const glm::vec3&			GetCameraUpVector() const
		{
			return m_upVector;
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

		inline const glm::mat4&			GetViewMatrixMat4() const
		{
			return m_viewMatrix;
		}

		inline const void				GetViewMatrixArray(float *viewMatrix) const
		{
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					*viewMatrix = m_viewMatrix[x][y];
					viewMatrix++;
				}
			}
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

		inline const void				GetProjectionArray(float *projection) const
		{
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					*projection = m_projectionMatrix[x][y];
					projection++;
				}
			}
		}

		void							Update();

		void							StrafeCamera(float amount);
		void							DollyCamera(float amount);
		void							PedCamera(float amount);
		void							RotateCamera(float yaw, float pitch, float roll);
		void							ZoomCamera(float amount);
};

#endif
