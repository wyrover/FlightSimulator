#include "Actor.h"

template <class ComponentType>
std::weak_ptr<ComponentType> Actor::GetComponent(ActorComponentID id)
{
	ActorComponents::iterator iter = m_actorComponents.find(id);

	if (iter != m_actorComponents.end)
	{
		return std::weak_ptr<ComponentType>(iter->second);
	}
	else
	{
		return nullptr;
	}
}