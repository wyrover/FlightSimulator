#include "Material.h"

Material::Material()
{
	m_pDiffuse = std::make_shared<Texture>();
	m_pSpecular = std::make_shared<Texture>();
}

Material::~Material()
{
}