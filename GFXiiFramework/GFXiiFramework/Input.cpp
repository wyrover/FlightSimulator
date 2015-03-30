#include "Input.h"

#define KEY_CODE_W 0x57
#define KEY_CODE_A 0x41
#define KEY_CODE_S 0x53
#define KEY_CODE_D 0x44
#define KEY_CODE_X 0x58
#define KEY_CODE_Z 0x5A
#define KEY_CODE_Q 0x51
#define KEY_CODE_E 0x45

Input::Input()
{
}

Input::~Input()
{
}

float Input::Forward()
{
	if ((unsigned short)GetKeyState(KEY_CODE_W) >> 15)
	{
		return 1.f;
	}
	else if ((unsigned short)GetKeyState(KEY_CODE_S) >> 15)
	{
		return -1.f;
	}
	return 0.f;
}

float Input::Horizontal()
{
	if ((unsigned short)GetKeyState(KEY_CODE_D) >> 15)
	{
		return 1.f;
	}
	else if ((unsigned short)GetKeyState(KEY_CODE_A) >> 15)
	{
		return -1.f;
	}
	return 0.f;
}

float Input::Vertical()
{
	if ((unsigned short)GetKeyState(KEY_CODE_X) >> 15)
	{
		return 1.f;
	}
	else if ((unsigned short)GetKeyState(KEY_CODE_Z) >> 15)
	{
		return -1.f;
	}
	return 0.f;
}

float Input::Roll()
{
	if ((unsigned short)GetKeyState(KEY_CODE_E) >> 15)
	{
		return 1.f;
	}
	else if ((unsigned short)GetKeyState(KEY_CODE_Q) >> 15)
	{
		return -1.f;
	}
	return 0.f;
}