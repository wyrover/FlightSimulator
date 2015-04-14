#pragma once
#include "DocumentObjectModel.h"
#include "Scene.h"

typedef std::map<ActorID, ActorPtr> ActorMap;

class ActorFactory final
{
private:
	ActorID						m_currentActorID;

	ActorMap					m_actors;

	void						CreateNewActor(const TagNodePtr pTagNode);
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

	const ActorMap&				CreateActorsFromDOM(const DocumentObjectModelPtr pDOM);
};

