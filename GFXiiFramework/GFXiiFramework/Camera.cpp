#include "Camera.h"
#include "Input.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	//std::shared_ptr<Transform> pTransform(m_pOwner->GetComponent<Transform>());

	//pTransform->Rotation(Input::Get().Yaw(), Input::Get().Pitch(), Input::Get().Roll());
	//pTransform->MoveForward(Input::Get().Forward());
	//pTransform->MoveHorizontal(Input::Get().Horizontal());
	//pTransform->MoveVertical(Input::Get().Vertical());

	ZoomCamera(Input::Get().GetZoom());
	UpdateViewMatrix();
}

void Camera::ZoomCamera(float amount)
{
	float newFOV = m_fov + amount;

	if (newFOV != m_fov && (newFOV > 30.0f && newFOV < 60.0f))
		SetProjection(newFOV, m_width, m_height, m_near, m_far);
}