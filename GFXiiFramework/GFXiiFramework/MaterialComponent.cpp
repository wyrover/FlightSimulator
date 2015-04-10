#include "MaterialComponent.h"

MaterialComponent::MaterialComponent()
{
	m_pDiffuse = std::make_shared<OGLTexture>();
	m_pSpecular = std::make_shared<OGLTexture>();
}

MaterialComponent::~MaterialComponent()
{
}