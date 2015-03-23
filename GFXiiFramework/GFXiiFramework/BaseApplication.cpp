#include "BaseApplication.h"
#include "OpenGL/OGLWindow.h"
#include "Resource.h"
#include <Windowsx.h>
#include "Input.h"

#define KEY_CODE_W 0x57
#define KEY_CODE_A 0x41
#define KEY_CODE_S 0x53
#define KEY_CODE_D 0x44
#define KEY_CODE_X 0x58
#define KEY_CODE_Z 0x5A
#define KEY_CODE_Q 0x51
#define KEY_CODE_E 0x45

BaseApplication* BaseApplication::s_oglapp = NULL;

BaseApplication::BaseApplication()
{
	m_appwnd = NULL;
	m_hInst = 0;
	m_terminate = FALSE;
}

BaseApplication::~BaseApplication()
{
	if ( m_appwnd )
		delete m_appwnd;
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

BaseApplication* BaseApplication::CreateApplication(HINSTANCE hinst)
{
	if ( ! s_oglapp )
	{
		s_oglapp = new BaseApplication();

		s_oglapp->m_hInst = hinst;
		s_oglapp->MyRegisterClass(hinst);

		//Now create an OGLWindow for this application
		s_oglapp->CreateApplicationWindow(1280, 720);
	}

	return s_oglapp;
}

void BaseApplication::DestroyApplication()
{
	if (s_oglapp)
		delete s_oglapp;
}

BaseApplication* BaseApplication::GetApplication()
{
	return s_oglapp;
}

void BaseApplication::CreateApplicationWindow(int width, int height)
{
	if (!m_appwnd)
	{
		m_appwnd = new OGLWindow();
		m_appwnd->InitWindow(m_hInst, width, height);
		m_appwnd->SetVisible(TRUE);
	}
}

int BaseApplication::Run()
{
	MSG msg;

	while (!m_terminate)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//peek for windows message
			if (msg.message == WM_QUIT)
			{
				Kill();
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		m_appwnd->Render();

		Input::Get().Update();
	}

	return (int)msg.wParam;
}

void BaseApplication::Kill()
{
	m_terminate = TRUE;
}

LRESULT CALLBACK BaseApplication::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_SIZE:
		s_oglapp->GetApplicationWindow()->Resize(LOWORD(lparam), HIWORD(lparam));
		break;

	case WM_CLOSE:
		s_oglapp->GetApplicationWindow()->DestroyRenderWindow();
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
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}