#include "CharacterController.h"
#include "Transform.h"
#include "Camera.h"
#include "Actor.h"
#include "Scene.h"
#include "ActorFactory.h"

CharacterController::CharacterController() : m_tick{ 0 }
{
}

CharacterController::~CharacterController()
{
}

ActorPtr CharacterController::Update()
{
	m_tick += 1;

	TransformPtr pTransform = m_pOwner->GetComponent<Transform>();

	pTransform->Rotation(Input::Get().Yaw(), Input::Get().Pitch(), Input::Get().Roll());
	pTransform->MoveForward(Input::Get().Forward());
	pTransform->MoveHorizontal(Input::Get().Horizontal());
	pTransform->MoveVertical(Input::Get().Vertical());

	m_pOwner->GetComponent<Camera>()->Update();

	// There needs to be delay between each shot, so 60 frames should be enough
	if (Input::Get().Fire() && m_tick > 60)
	{
		m_tick = 0;

		const glm::vec3 offset = GetComponent<Transform>()->GetViewVector() * 5.0f;

		ActorPtr pActor = ActorFactory::Get().CreateActorFromPrefab(m_pProjectilePrefab);

		pActor->GetComponent<Transform>()->SetPosition(pTransform->GetPosition() + offset);
		pActor->GetComponent<Transform>()->SetOrientation(pTransform->GetOrientation());
		pActor->GetComponent<Rigidbody>()->SetTimer(true);

		pActor->SetTag("missile");

		m_projectiles.push_back(pActor);

		return pActor;
	}

	for (const ActorPtr &pActor : m_projectiles)
	{
		pActor->GetComponent<Transform>()->MoveForward(2.0f);
	}

	return nullptr;
}

void CharacterController::RemoveProjectile(const ActorPtr pActor)
{
	for (unsigned index = 0; index < m_projectiles.size(); index++)
	{
		if (m_projectiles[index]->GetID() == pActor->GetID())
		{
			m_projectiles.erase(m_projectiles.begin() + index);
			break;
		}
	}
}

ActorPtr CharacterController::UpdateProjectiles()
{
	bool removeProjectile = false;
	ActorPtr pActorToRemove = nullptr;

	for (ActorPtr &pActor : m_projectiles)
	{
		if (pActor->GetComponent<Rigidbody>()->Update())
		{
			pActorToRemove = pActor;
			removeProjectile = true;
		}
	}

	if (removeProjectile)
	{
		RemoveProjectile(pActorToRemove);
	}
	return pActorToRemove;
}