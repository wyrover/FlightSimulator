#pragma once
#include "ActorComponent.h"
#include "OpenGL\OGLTexture.h"
#include "OpenGL\OGLCube.h"

typedef std::shared_ptr<OGLTexture> TexturePtr;

class SkyBoxComponent : public ActorComponent, public OGLCube
{
private:
	TexturePtr								m_textures[6];

public:
	SkyBoxComponent();
	virtual ~SkyBoxComponent();

	static const ActorComponentID			COMPONENT_ID = 5;

	inline virtual ActorComponentID			GetComponentID() override
	{
		return COMPONENT_ID;
	}

	virtual void							Render() const;
	void									Init(const char* front, const char* back, const char* left, const char* right, const char* top, const char* bottom);
};

