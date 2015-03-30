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
		virtual				~RenderWindow() {;}

		virtual BOOL		InitWindow(HINSTANCE hInstance, int width, int height) = 0;

		virtual void		Render() = 0;
		virtual void		Resize( int width, int height ) = 0;
		
		void				SetVisible( BOOL visible )
		{
			ShowWindow ( m_hwnd, visible? SW_SHOW : SW_HIDE );
		}
		
		virtual void		DestroyRenderWindow() = 0;
};