#include "MaterialComponent.h"

MaterialComponent::MaterialComponent()
{
	m_pDiffuse = std::make_shared<Texture>();
	m_pSpecular = std::make_shared<Texture>();
}

MaterialComponent::~MaterialComponent()
{
}