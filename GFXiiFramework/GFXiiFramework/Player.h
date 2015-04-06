#pragma once
#include "OpenGL\OGLMesh.h"
#include "OpenGL\OGLCamera.h"

class Player final
{
private:
	Player();
	~Player();

	OGLCamera					*m_camera;
	GameObject					*m_gameObject;

	glm::vec3					m_cameraOffset;

public:
	inline static Player&		Get()
	{
		static Player player;

		return player;
	}

	inline void					SetCamera(OGLCamera *camera) { m_camera = camera; }
	inline void					SetCurrentGameObject(GameObject *gameObject) { m_gameObject = gameObject; }

	inline const OGLCamera*		GetCamera() const { return m_camera; }
	inline const GameObject*	GetCurrentGameObject() const { return m_gameObject; }

	void					Update();
};