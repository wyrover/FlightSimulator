#include "BaseApplication.h"
#include "Resource.h"
#include "Input.h"
#include <Windowsx.h>

BaseApplication BaseApplication::m_pApplication;
BOOL BaseApplication::m_registered = FALSE;

BaseApplication::BaseApplication()
{
	m_hInst = 0;
	m_registered = m_terminate = FALSE;
}

BaseApplication::~BaseApplication()
{
}

BOOL BaseApplication::MyRegisterClass(HINSTANCE hinst)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= this->WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hinst;
	wcex.hIcon			= LoadIcon(hinst, MAKEINTRESOURCE(IDI_OGLWIN32));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"RenderWindow";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	if ( !RegisterClassEx ( &wcex ) )
		return FALSE;

	return TRUE;
}

BaseApplication BaseApplication::CreateApplication(HINSTANCE hinst)
{
	if (!m_registered)
	{
		m_pApplication.m_hInst = hinst;
		m_pApplication.MyRegisterClass(hinst);

		m_pApplication.CreateApplicationWindow(1280, 720);
	}

	return m_pApplication;
}

void BaseApplication::DestroyApplication()
{
}

BaseApplication BaseApplication::GetApplication()
{
	return m_pApplication;
}

void BaseApplication::CreateApplicationWindow(int width, int height)
{
	if (!m_pWindow)
	{
		m_pWindow = std::make_unique<ApplicationWindow>();
		m_pWindow->InitWindow(m_hInst, width, height);
		m_pWindow->SetVisible(TRUE);
	}
}

int BaseApplication::Run()
{
	MSG msg;

	while ( !m_terminate )
	{
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			//peek for windows message
			if ( msg.message == WM_QUIT )
			{
				Kill();
			}
			else
			{
				TranslateMessage ( &msg );
				DispatchMessage ( &msg );
			}
		}
		m_pWindow->Render();

		Input::Get().Update();
	}

	return (int) msg.wParam;
}

void BaseApplication::Kill()
{
	m_terminate = TRUE;
}

LRESULT CALLBACK BaseApplication::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch ( msg )
	{
		case WM_SIZE:
			m_pApplication.GetApplicationWindow()->Resize(LOWORD(lparam), HIWORD(lparam));
			break;

		case WM_CLOSE:
			m_pApplication.GetApplicationWindow()->DestroyRenderWindow();
			break;

		case WM_LBUTTONUP:
			Input::Get().LeftMouseButtonDown(false);
			break;

		case WM_LBUTTONDOWN:
			Input::Get().LeftMouseButtonDown(true);
			break;

		case WM_MOUSEWHEEL:
			Input::Get().SetZoom((short)HIWORD(wparam));
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc( hwnd, msg, wparam, lparam );
	}

	return 0;
}