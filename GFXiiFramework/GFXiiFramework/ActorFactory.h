#pragma once
#include "DocumentObjectModel.h"
#include "Actor.h"
#include "glm\vec3.hpp"

typedef std::shared_ptr<std::map<ActorID, ActorPtr>> ActorMap;

class ActorFactory final
{
private:
	ActorID						m_currentActorID;

	ActorMap					m_pActors;

	void						CreateNewActor(const TagNodePtr pTagNode);
	void						AddNewComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;

	void						AddNewTransformComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	void						AddNewMeshComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	void						AddNewMaterialComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	void						AddNewCharacterControllerComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	void						AddNewCameraComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	void						AddNewSkyBoxComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	void						AddNewLightComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	void						AddNewRigidbodyComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;
	void						AddNewBillboardComponent(ActorPtr pActor, const TagNodePtr pTagNode) const;

	const glm::vec3				GetXYZ(std::map<std::string, std::string> data) const;
	const glm::vec3				GetRGB(std::map < std::string, std::string> data) const;

	const Renderer				GetRenderer(const TagNodePtr pTagNode) const;

public:
	ActorFactory();
	virtual						~ActorFactory();

	const ActorMap				CreateActorsFromDOM(const DocumentObjectModelPtr pDOM);
};

