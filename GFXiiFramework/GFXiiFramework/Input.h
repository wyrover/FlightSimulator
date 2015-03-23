#pragma once
#include "glm\glm.hpp"
#include <Windows.h>
#include <iostream>

class Input final
{
public:
	virtual ~Input();

	inline static Input& Get()
	{
		static Input input;

		return input;
	}

	// Call at the end of the frame
	inline void Update()
	{
		UpdateMousePositions();
	}

	inline void LeftMouseButtonDown(bool mouseDown)
	{
		m_leftMouseButtonDown = mouseDown;
	}
	
	// Translations
	float Forward();
	float Horizontal();
	float Vertical();

	// Rotations
	float Pitch();
	float Yaw();
	float Roll();

	void SetZoom(int zoomDirection)
	{
		m_zoomDirection = zoomDirection > 0.f ? -1.f : 1.f;
	}

	inline int GetZoom()
	{
		return m_zoomDirection;
	}

private:
	Input();

	POINT m_mousePosition;
	POINT m_mousePositionLastFrame;

	bool m_leftMouseButtonDown;
	int m_zoomDirection;

	inline void UpdateMousePositions()
	{
		m_mousePositionLastFrame = m_mousePosition;
	}
};

