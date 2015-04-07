#pragma once

#include "OpenGL\OGLCube.h"

class OGLSkyBox : public OGLCube
{
private:
	OGLTexture				m_textures[6];

public:
	OGLSkyBox();
	~OGLSkyBox();

	void					Init(const char* front, const char* back, const char* left, const char* right, const char* top, const char* bottom);

	virtual void			Render() const;
};

