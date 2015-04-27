#pragma once
#include "glm\glm.hpp"
#include <Windows.h>
#include <iostream>

#define KEY_CODE_SPACE 0x20

class Input final
{
public:
	virtual ~Input();

	inline static Input&	Get()
	{
		static Input input;

		return input;
	}

	// Call at the end of the frame
	inline void				Update()
	{
		GetCursorPos(&m_mousePosition);

		if (m_leftMouseButtonDown && m_mousePosition.y != m_mousePositionLastFrame.y)
			m_pitch = (m_mousePosition.y - m_mousePositionLastFrame.y) > 0.f ? 1.f : -1.f;
		else
			m_pitch = 0;

		if (m_leftMouseButtonDown && m_mousePosition.x != m_mousePositionLastFrame.x)
			m_yaw = (m_mousePosition.x - m_mousePositionLastFrame.x) > 0.f ? 1.f : -1.f;
		else
			m_yaw = 0;

		if ((unsigned short)GetKeyState(KEY_CODE_SPACE) >> 15)
		{
			m_spaceDown = true;
		}
		else
		{
			m_spaceDown = false;
		}

		UpdateMousePositions();
	}

	inline void				LeftMouseButtonDown(bool mouseDown)
	{
		m_leftMouseButtonDown = mouseDown;
	}
	
	// Translations
	float Forward();
	float Horizontal();
	float Vertical();

	// Rotations
	float Roll();

	inline float			Pitch()
	{
		return m_pitch;
	}

	inline float			Yaw()
	{
		return m_yaw;
	}

	inline bool				Fire()
	{
		return m_spaceDown;
	}

	void					SetZoom(int zoomDirection)
	{
		m_zoomDirection = zoomDirection > 0 ? -1 : 1;
	}

	inline float			GetZoom()
	{
		float result = (float)m_zoomDirection;

		m_zoomDirection = 0;

		return result;
	}

private:
	Input();

	POINT					m_mousePosition;
	POINT					m_mousePositionLastFrame;

	float					m_yaw;
	float					m_roll;
	float					m_pitch;

	bool					m_spaceDown;
	bool					m_leftMouseButtonDown;
	int						m_zoomDirection;

	inline void				UpdateMousePositions()
	{
		m_mousePositionLastFrame = m_mousePosition;
	}
};

