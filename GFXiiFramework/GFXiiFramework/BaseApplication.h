#pragma once

#include <Windows.h>
#include "ApplicationWindow.h"

typedef std::shared_ptr<ApplicationWindow> WindowPtr;

//Define BaseApplication as a singleton
class BaseApplication
{
private:
	WindowPtr									m_pWindow;
	static BaseApplication						m_pApplication;
	static BOOL									m_registered;
	BOOL										m_terminate;
		
												BaseApplication();
	void										CreateApplicationWindow(int width, int height);
	BOOL										MyRegisterClass(HINSTANCE hinst);

public:
	virtual										~BaseApplication();

	HINSTANCE									m_hInst;

	static BaseApplication						CreateApplication(HINSTANCE hInst);
	static BaseApplication						GetApplication();
	static void									DestroyApplication();

		
	int											Run();
	void										Kill();
		

	inline WindowPtr							GetApplicationWindow()
	{
		return m_pWindow;
	}

	static	LRESULT CALLBACK					WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};