#pragma once
#include "DocumentObjectModel.h"
#include "Scene.h"

class ActorFactory final
{
private:
	void						CreateNewActor(const TagNodePtr pTag, ScenePtr pScene);
	void						CreateNewComponent(const TagNodePtr pTag, ActorPtr pActor);

	void						CreateNewTransformComponent(const TagNodePtr, ActorPtr pActor);

public:
	ActorFactory();
	virtual						~ActorFactory();

	void						CreateActors(const DocumentObjectModelPtr pDOM, ScenePtr pScene);
};

