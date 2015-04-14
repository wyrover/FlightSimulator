#pragma once
#include "GLSLShader.h"
#include "MeshNode.h"
#include "Camera.h"

class MeshShader : public GLSLShaderProgram
{
private:
	struct Uniforms
	{
		int modelview, projection, localToWorld, cameraPosition, rotation, bCalculateSpecular;
	};

	Uniforms				m_uniforms;

public:
	MeshShader();
	virtual					~MeshShader();

	const Uniforms			GetUniforms() const
	{
		return m_uniforms;
	}

	void					PreRender();

	inline void				PostRender()
	{
		DeactivateShaderProgram();
	}

	void					AttachAndBuildProgram(const LPWSTR vertexShader = nullptr, const LPWSTR fragmentShader = nullptr);
	void					UpdateUniformValues(const MeshNodePtr pSceneNode = nullptr, const CameraPtr pCamera = nullptr) const;
};

