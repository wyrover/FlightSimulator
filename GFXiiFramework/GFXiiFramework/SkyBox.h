#pragma once
#include "ActorComponent.h"
#include "Texture.h"
#include "Cube.h"

class SkyBox;

typedef std::shared_ptr<SkyBox> SkyBoxPtr;
typedef std::shared_ptr<Texture> TexturePtr;

class SkyBox : public ActorComponent, public Cube
{
private:
	TexturePtr								m_textures[6];

public:
	SkyBox();
	virtual ~SkyBox();

	static const ActorComponentID			COMPONENT_ID = 5;

	inline virtual ActorComponentID			GetComponentID() const override
	{
		return COMPONENT_ID;
	}

	virtual void							Render() const;
	void									Init(const char* front, const char* back, const char* left, const char* right, const char* top, const char* bottom);
};

