#pragma once

#include "RenderWindow.h"
#include "OGLCube.h"
#include "OGLMesh.h"
#include "OGLShader.h"
#include "OGLTexture.h"
#include "OGLCamera.h"
#include "..\Player.h"
#include "..\OGLSkyBox.h"
#include "../Actor.h"

class OGLWindow : public RenderWindow
{
	private:
		HDC						m_hdc;				//handle to a device context
		HGLRC					m_hglrc;			//handle to a gl rendering context

		int						m_width;
		int						m_height;
		
		float					m_rotY;

		// TODO: Store in a container
		OGLSkyBox				*m_skyBox;
		GameObject				*m_house;
		GameObject				*m_aircraft;

		std::shared_ptr<Actor>	m_pHouse;

		//Declear an OGL shader program
		OGLShaderProgram		*m_shader;
		OGLShaderProgram		*m_skyBoxShader;

		int						m_uniform_modelview;
		int						m_uniform_projection;
		int						m_uniform_local_to_world;
		int						m_uniform_camera_position;
		int						m_uniform_rotation;

		//int						m_uniform_texture;

		int						m_texDefaultSampler;

		OGLCamera				*m_camera;

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
