#pragma once
#include "ActorComponent.h"
#include "Texture.h"

class Material;

typedef std::shared_ptr<Material> MaterialPtr;
typedef std::shared_ptr<Texture> TexturePtr;

class Material : public ActorComponent
{
private:
	TexturePtr							m_pDiffuse;
	TexturePtr							m_pSpecular;
	TexturePtr							m_pNormal;

public:
	Material();
	virtual ~Material();

	static const ActorComponentID		 COMPONENT_ID = 2;

	inline virtual ActorComponentID		GetComponentID() const override { return COMPONENT_ID; }

	inline const TexturePtr				GetDiffuse() { return m_pDiffuse; }
	inline const TexturePtr				GetSpecular() { return m_pSpecular; }
	inline const TexturePtr				GetNormal() { return m_pNormal; }

	inline void							SetDiffuse(const char* file)
	{
		if (!m_pDiffuse)
		{
			m_pDiffuse = std::make_shared<Texture>();
		}
		m_pDiffuse->CreateTextureFromFile(file);
	}
	inline void							SetSpecular(const char* file)
	{
		if (!m_pSpecular)
		{
			m_pSpecular = std::make_shared<Texture>();
		}
		m_pSpecular->CreateTextureFromFile(file);
	}
	inline void							SetNormal(const char* file)
	{
		if (!m_pNormal)
		{
			m_pNormal = std::make_shared<Texture>();
		}
		m_pNormal->CreateTextureFromFile(file);
	}
};

