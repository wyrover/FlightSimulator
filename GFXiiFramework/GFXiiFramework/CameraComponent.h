#pragma once
#include "ActorComponent.h"
#include "TransformComponent.h"
#include "Actor.h"
#include "glm\gtc\matrix_transform.hpp"

class CameraComponent : public ActorComponent
{
private:
	glm::mat4						m_viewMatrix;
	glm::mat4						m_projectionMatrix;
	float							m_fov;
	float							m_aspectRatio;
	float							m_width;
	float							m_height;
	float							m_near;
	float							m_far;

public:
	CameraComponent();
	virtual ~CameraComponent();

	static const ActorComponentID			COMPONENT_ID = 4;

	inline virtual ActorComponentID			GetComponentID() override
	{
		return COMPONENT_ID;
	}

	void									UpdateViewMatrix()
	{
		
		std::shared_ptr<TransformComponent> pTransformComponent(m_pOwner->GetComponent<TransformComponent>());

		m_viewMatrix = glm::lookAt(pTransformComponent->GetPosition(), pTransformComponent->GetPosition() + pTransformComponent->GetViewVector(), pTransformComponent->GetUpVector());
	}

	inline void						SetCameraFOV(float fov)
	{
		m_fov = fov;
	}

	inline float					GetCameraFOV() const
	{
		return m_fov;
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

