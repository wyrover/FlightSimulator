#pragma once
#include "ActorComponent.h"
#include "OpenGL\OGLTexture.h"

typedef std::shared_ptr<OGLTexture> TexturePtr;

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

	inline const OGLTexture&			GetDiffuse() { return *m_pDiffuse; }
	inline const OGLTexture&			GetSpecular() { return *m_pSpecular; }

	inline void							SetDiffuse(const char* file)
	{
		m_pDiffuse->CreateTextureFromFile(file);
	}
	inline void							SetSpecular(const char* file)
	{
		m_pSpecular->CreateTextureFromFile(file);
	}
};

