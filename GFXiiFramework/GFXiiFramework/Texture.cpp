#if WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

#include "Texture.h"
#include "ImageIO.h"

Texture::Texture()
{
	m_syshandle = m_apphandle = -1;
}

Texture::~Texture()
{
	FreeTexture();
}

void Texture::CreateTextureFromFile(const char* filename)
{
	if(m_syshandle != -1 || m_apphandle != -1)
	{
		return;
	}

	unsigned char *buffer = NULL;
	int width;
	int height;
	int bpp;
	int nChannels;

	if(ImageIO::LoadTGA(filename, &buffer, &width, &height, &bpp, &nChannels) != E_IMAGEIO_SUCCESS)
	{
		return;
	}
	
	if(buffer == NULL)//this shouldn't happen, but let's do it anyway.
	{
		return;
	}

	glGenTextures(1, &m_syshandle);
	glBindTexture(GL_TEXTURE_2D, m_syshandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if(nChannels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	}
	else if(nChannels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	}

	free(buffer);
}

void Texture::CreateTextureFromData(void* data, int type, int width, int height, int bits)
{

}

void Texture::CreateTextureAsRenderTarget(int width, int height)
{
	glGenTextures(1, &m_syshandle);
	glBindTexture(GL_TEXTURE_2D, m_syshandle);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Texture::CreateTextureAsDepthTarget(int width, int height)
{
	glGenTextures(1, &m_syshandle);
	glBindTexture(GL_TEXTURE_2D, m_syshandle);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}


void Texture::FreeTexture()
{
	if(m_syshandle != -1)
	{
		m_syshandle = -1;
		m_apphandle = -1;
		glDeleteTextures(1, &m_syshandle);
	}
}
