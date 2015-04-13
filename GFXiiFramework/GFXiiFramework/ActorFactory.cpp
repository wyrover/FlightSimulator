#include "ActorFactory.h"
#include "Transform.h"

ActorFactory::ActorFactory()
{
}

ActorFactory::~ActorFactory()
{
}

void ActorFactory::CreateActors(const DocumentObjectModelPtr pDOM, ScenePtr pScene)
{
	TagNodePtr pTagIndex = pDOM->GetRoot();

	// Check root
	if (pTagIndex && pTagIndex->name == "ActorFactory")
	{
		for (const TagNodePtr pTag : pTagIndex->children)
		{
			if (pTag->name == "Actor")
			{
				CreateNewActor(pTag, pScene);
			}
		}
	}
}

void ActorFactory::CreateNewActor(const TagNodePtr pTag, ScenePtr pScene)
{
	ActorPtr pNewActor = std::make_shared<Actor>();

	for (const TagNodePtr pTagNode : pTag->children)
	{
		if (pTagNode->name == "ActorComponent")
		{
			// Actor components store one component only
			CreateNewComponent(pTagNode->children.front(), pNewActor);
		}
	}

	
}

void ActorFactory::CreateNewComponent(const TagNodePtr pTag, ActorPtr pActor)
{
	if (pTag->name == "Position")
	{
		CreateNewTransformComponent(pTag, pActor);
	}
}

void ActorFactory::CreateNewTransformComponent(const TagNodePtr pTag, ActorPtr pActor)
{
	TransformPtr pTransform = std::make_shared<Transform>();

	glm::vec3 position;

	for (const TagNodePtr pComponent : pTag->children)
	{
		if (pComponent->name == "X")
		{
			position.x = (float)atof(pComponent->data.c_str());
		}
		else if (pComponent->name == "Y")
		{
			position.y = (float)atof(pComponent->data.c_str());
		}
		else
		{
			position.z = (float)atof(pComponent->data.c_str());
		}
	}

	pTransform->SetPosition(position);
	pTransform->SetOwner(pActor);

	pActor->AddComponent(pTransform);
}