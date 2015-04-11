#pragma once
#include "ActorComponent.h"
#include "Texture.h"

typedef std::shared_ptr<Texture> TexturePtr;

class MaterialComponent : public ActorComponent
{
private:
	TexturePtr							m_pDiffuse;
	TexturePtr							m_pSpecular;

public:
	MaterialComponent();
	virtual ~MaterialComponent();

	static const ActorComponentID		 COMPONENT_ID = 2;

	inline virtual ActorComponentID		GetComponentID() override { return COMPONENT_ID; }

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

