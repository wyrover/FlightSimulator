#pragma once

class Texture
{
	private:

	public:
		unsigned int					m_syshandle;
		unsigned int					m_apphandle;

	public:
										Texture();
		virtual							~Texture();

		virtual void					CreateTextureFromFile(const char* filename);
		virtual void					CreateTextureFromData(void* data, int type, int width, int height, int bits);

		virtual void					CreateTextureAsRenderTarget(int width, int height);

		virtual void					CreateTextureAsDepthTarget(int width, int height);
		virtual void					FreeTexture();
};