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
	m_yaw = m_roll = m_pitch = 0.0f;
}

Input::~Input()
{
}

float& Input::Forward()
{
	float result = 0.0f;

	if ((unsigned short)GetKeyState(KEY_CODE_W) >> 15)
	{
		result = 1.0f;
	}
	else if ((unsigned short)GetKeyState(KEY_CODE_S) >> 15)
	{
		result = -1.0f;
	}
	return result;
}

float& Input::Horizontal()
{
	float result = 0.0f;

	if ((unsigned short)GetKeyState(KEY_CODE_D) >> 15)
	{
		result = 1.0f;
	}
	else if ((unsigned short)GetKeyState(KEY_CODE_A) >> 15)
	{
		result = -1.0f;
	}
	return result;
}

float& Input::Vertical()
{
	float result = 0.0f;

	if ((unsigned short)GetKeyState(KEY_CODE_X) >> 15)
	{
		result = 1.f;
	}
	else if ((unsigned short)GetKeyState(KEY_CODE_Z) >> 15)
	{
		result = -1.f;
	}
	return result;
}

float& Input::Roll()
{
	float result = 0.0f;

	if ((unsigned short)GetKeyState(KEY_CODE_E) >> 15)
	{
		result = 1.0f;
	}
	else if ((unsigned short)GetKeyState(KEY_CODE_Q) >> 15)
	{
		result = -1.0f;
	}
	return result;
}