//Created for Graphics I and II
//Author: Minsi Chen

#include "OGLCamera.h"
#include "..\GLM\gtc\quaternion.hpp"
#include "..\Input.h"

void OGLCamera::Update()
{
	//Rotation(Input::Get().Yaw(), Input::Get().Pitch(), Input::Get().Roll());
	//MoveForward(Input::Get().Forward());
	//MoveHorizontal(Input::Get().Horizontal());
	//MoveVertical(Input::Get().Vertical());

	ZoomCamera(Input::Get().GetZoom());
	UpdateViewMatrix();
}

void OGLCamera::ZoomCamera(float amount)
{
	float newFOV = m_fov + amount;

	if (newFOV != m_fov && (newFOV > 30.0f && newFOV < 60.0f))
		SetProjection(newFOV, m_width, m_height, m_near, m_far);
}