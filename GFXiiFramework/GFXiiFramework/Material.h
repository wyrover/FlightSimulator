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

public:
	Material();
	virtual ~Material();

	static const ActorComponentID		 COMPONENT_ID = 2;

	inline virtual ActorComponentID		GetComponentID() const override { return COMPONENT_ID; }

	inline const Texture&			GetDiffuse() { return *m_pDiffuse; }
	inline const Texture&			GetSpecular() { return *m_pSpecular; }

	inline void							SetDiffuse(const char* file)
	{
		m_pDiffuse->CreateTextureFromFile(file);
	}
	inline void							SetSpecular(const char* file)
	{
		m_pSpecular->CreateTextureFromFile(file);
	}
};

