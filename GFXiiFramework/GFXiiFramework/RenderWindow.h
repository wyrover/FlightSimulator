#pragma once

#include <Windows.h>

class RenderWindow
{
	protected:
		HWND		m_hwnd;				//handle to a window
		int			m_width;
		int			m_height;
				
	public:
							RenderWindow() {;}
							RenderWindow(HINSTANCE hInstance, int width, int height);
		virtual				~RenderWindow() {;}

		virtual BOOL		InitWindow(HINSTANCE hInstance, int width, int height) = 0;

		virtual void		Render() = 0;
		virtual void		Resize( int width, int height ) = 0;
		
		void				SetVisible( BOOL visible )
		{
			ShowWindow ( m_hwnd, visible? SW_SHOW : SW_HIDE );
		}
		
		virtual void		DestroyRenderWindow() = 0;

		virtual BOOL		MouseLBDown (int x, int y) = 0;
		virtual BOOL		MouseLBUp (int x, int y) = 0;
		virtual BOOL		MouseMove (int x, int y) = 0;
		virtual BOOL		MouseWheel(int val) = 0;
		virtual BOOL		KeyPressW() = 0;
		virtual BOOL		KeyPressS() = 0;
		virtual BOOL		KeyPressA() = 0;
		virtual BOOL		KeyPressD() = 0;
		virtual BOOL		KeyPressZ() = 0;
		virtual BOOL		KeyPressX() = 0;
		virtual BOOL		KeyPressQ() = 0;
		virtual BOOL		KeyPressE() = 0;
};