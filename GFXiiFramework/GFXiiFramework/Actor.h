#pragma once
#include <map>
#include <memory>
#include "ActorComponent.h"

class ActorComponent;

typedef unsigned int ActorID, ActorComponentID;

typedef std::shared_ptr<ActorComponent> ActorComponentPtr;
typedef std::map<ActorComponentID, ActorComponentPtr> ActorComponents;

enum Renderer { Renderer_Mesh, Renderer_SkyBox, Renderer_Light, Renderer_Billboard, Renderer_Pass, Renderer_ProjectilePrefab };

class Actor
{
private:
	ActorID							m_ID;
	ActorComponents					m_actorComponents;
	Renderer						m_renderer;
	std::string						m_tag;

public:
	Actor(const ActorID id, const Renderer renderer) : m_ID{ id }, m_renderer{ renderer } { }

	virtual ~Actor() { }

	template <class ComponentType>
	std::shared_ptr<ComponentType>	GetComponent()
	{
		ActorComponentPtr pActorComponent = std::make_shared<ComponentType>();

		ActorComponents::iterator iter = m_actorComponents.find(pActorComponent->GetComponentID());
		
		if (iter != m_actorComponents.end())
		{
			return std::shared_ptr<ComponentType>(std::tr1::static_pointer_cast<ComponentType>(iter->second));
		}
		else
		{
			return nullptr;
		}
	}

	inline const Renderer			GetRenderer() const { return m_renderer; }
	inline const ActorID			GetID() const { return m_ID; }

	inline void						AddComponent(const ActorComponentPtr pComponent)
	{
		// TODO: Check only one component of each type is attached
		m_actorComponents[pComponent->GetComponentID()] = pComponent;
	}

	inline void						SetTag(const std::string tag)
	{
		m_tag = tag;
	}

	inline const std::string		GetTag() const
	{
		return m_tag;
	}
};
