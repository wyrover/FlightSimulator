#pragma once
#include "ActorComponent.h"
#include "Transform.h"
#include "Actor.h"
#include "glm\gtc\matrix_transform.hpp"

class Camera;

typedef std::shared_ptr<Camera> CameraPtr;
typedef std::weak_ptr<Camera> WeakCameraPtr;

class Camera : public ActorComponent
{
private:
	glm::mat4								m_viewMatrix;
	glm::mat4								m_projectionMatrix;
	float									m_fov;
	float									m_aspectRatio;
	float									m_width;
	float									m_height;
	float									m_near;
	float									m_far;

	glm::vec3								m_cameraPosition;

public:
	Camera();
	virtual ~Camera();

	static const ActorComponentID			COMPONENT_ID = 4;

	inline virtual ActorComponentID			GetComponentID() const override
	{
		return COMPONENT_ID;
	}

	void									UpdateViewMatrix()
	{
		// Set camera to follow behind the actor
		TransformPtr pTransform = m_pOwner->GetComponent<Transform>();

		glm::vec3 offsetPosition = (pTransform->GetPosition() - pTransform->GetViewVector() * 12.0f) + (pTransform->GetUpVector() * 4.0f);

		m_cameraPosition = offsetPosition;

		m_viewMatrix = glm::lookAt(offsetPosition, offsetPosition + pTransform->GetViewVector(), pTransform->GetUpVector());
	}

	inline void						SetCameraFOV(float fov)
	{
		m_fov = fov;
	}

	inline float					GetCameraFOV() const
	{
		return m_fov;
	}

	inline const glm::vec3			GetPosition() const
	{
		return m_cameraPosition;
	}

	inline void						SetCameraAspectRatio(float ar)
	{
		m_aspectRatio = ar;
	}

	inline float					GetCameraAspectRatio() const
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

	inline void						SetProjection(float fov, float width, float height, float nPlane, float fPlane)
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

