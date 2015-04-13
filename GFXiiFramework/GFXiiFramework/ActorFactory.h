#pragma once
#include "DocumentObjectModel.h"
#include "Scene.h"

class ActorFactory final
{
private:
	void						CreateNewActor(ScenePtr pScene, const TagNodePtr pTagNode) const;
	void						AddNewComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;

	void						AddNewTransformComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	void						AddNewMeshComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	//void						AddNewMaterialComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	//void						AddNewCharacterControllerComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	//void						AddNewCameraController(ActorPtr pActor, const TagNodePtr pTagNode) const;
	//void						AddNewSkyBoxController(ActorPtr pActor, const TagNodePtr pTagNode) const;

	const glm::vec3				GetXYZ(std::map<std::string, std::string> data) const;

public:
	ActorFactory();
	virtual						~ActorFactory();

	void						CreateSceneFromDOM(ScenePtr pScene, const DocumentObjectModelPtr pDOM) const;
};

