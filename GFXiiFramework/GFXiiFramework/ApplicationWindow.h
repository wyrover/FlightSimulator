#pragma once

#include <Windows.h>
#include "Cube.h"
#include "Texture.h"
#include "Player.h"
#include "Actor.h"
#include "Scene.h"
#include "XMLReader.h"
#include "ActorFactory.h"

class ApplicationWindow
{
	private:
		HDC						m_hdc;				//handle to a device context
		HGLRC					m_hglrc;			//handle to a gl rendering context
		HWND					m_hwnd;

		int						m_width;
		int						m_height;
		
		float					m_rotY;

		// NEW FANCY STUFF YEAH!?
		ActorPtr				m_pHouse;
		ActorPtr				m_pSkyBox;
		ActorPtr				m_pArc170;

		// Store the scene nodes
		ScenePtr				m_pScene;

		int						m_uniform_modelview;
		int						m_uniform_projection;
		int						m_uniform_local_to_world;
		int						m_uniform_camera_position;
		int						m_uniform_rotation;

protected:

		HGLRC					CreateOGLContext (HDC hdc);
		BOOL					DestroyOGLContext();
		void					InitOGLState();

	public:
								ApplicationWindow();
								~ApplicationWindow();

		void					SetVisible( BOOL visible )
		{
			ShowWindow ( m_hwnd, visible? SW_SHOW : SW_HIDE );
		}
		
		BOOL					InitWindow(HINSTANCE hInstance, int width, int height);

		void					Render();
		void					Resize( int width, int height );
		void					DestroyRenderWindow();
};
