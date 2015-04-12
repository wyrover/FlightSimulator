#include "CharacterController.h"
#include "Transform.h"
#include "Camera.h"
#include "Actor.h"

CharacterController::CharacterController()
{
}

CharacterController::~CharacterController()
{
}

void CharacterController::Update()
{
	TransformPtr pTransform = m_pOwner->GetComponent<Transform>();

	pTransform->Rotation(Input::Get().Yaw(), Input::Get().Pitch(), Input::Get().Roll());
	pTransform->MoveForward(Input::Get().Forward());
	pTransform->MoveHorizontal(Input::Get().Horizontal());
	pTransform->MoveVertical(Input::Get().Vertical());

	m_pOwner->GetComponent<Camera>()->Update();
}