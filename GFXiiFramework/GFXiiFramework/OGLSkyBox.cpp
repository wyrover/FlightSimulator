#include "OGLSkyBox.h"

OGLSkyBox::OGLSkyBox()
{
}

OGLSkyBox::~OGLSkyBox()
{
	delete[] m_textures;
}

void OGLSkyBox::Init(const char* front, const char* back, const char* left, const char* right, const char* top, const char* bottom)
{
	OGLTexture frontTexture, backTexture, leftTexture, rightTexture, topTexture, bottomTexture;

	// Create textures
	frontTexture.CreateTextureFromFile(front);
	backTexture.CreateTextureFromFile(back);
	leftTexture.CreateTextureFromFile(left);
	rightTexture.CreateTextureFromFile(right);
	topTexture.CreateTextureFromFile(top);
	bottomTexture.CreateTextureFromFile(bottom);

	// Store textures
	m_textures[0] = &frontTexture;
	m_textures[1] = &backTexture;
	m_textures[2] = &leftTexture;
	m_textures[3] = &rightTexture;
	m_textures[4] = &topTexture;
	m_textures[5] = &bottomTexture;
}

void OGLSkyBox::Render() const
{

}