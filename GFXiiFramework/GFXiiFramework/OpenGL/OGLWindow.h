#pragma once

#include "RenderWindow.h"
#include "OGLCube.h"
#include "OGLMesh.h"
#include "OGLShader.h"
#include "OGLTexture.h"
#include "OGLCamera.h"

class OGLWindow : public RenderWindow
{
	private:
		HDC			m_hdc;				//handle to a device context
		HGLRC		m_hglrc;			//handle to a gl rendering context

		int			m_width;
		int			m_height;
		
		//This is not an ideal place to hold geometry data
		GameObject		*m_house;

		//Declear an OGL shader program
		OGLShaderProgram		*m_shader;
		int						m_uniform_modelview;
		int						m_uniform_projection;
		int                     m_uniform_texture;
		int						m_texDefaultSampler;

		OGLCamera				m_camera;

protected:

		HGLRC CreateOGLContext (HDC hdc);
		BOOL DestroyOGLContext();
		void InitOGLState();

	public:
					OGLWindow();
					~OGLWindow();
		
		BOOL		InitWindow(HINSTANCE hInstance, int width, int height);

		void		Render();
		void		Resize( int width, int height );
		void		DestroyRenderWindow();
};
