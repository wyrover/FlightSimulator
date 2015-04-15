#pragma once
#include "GLSLShader.h"
#include "MeshNode.h"
#include "Camera.h"
#include "LightNode.h"

class MeshShader;

typedef std::shared_ptr<MeshShader> MeshShaderPtr;

class MeshShader : public GLSLShaderProgram
{
private:
	struct Uniforms
	{
		int modelview, projection, localToWorld, cameraPosition, rotation, bCalculateSpecular, lightPosition, lightColour;
	};

	Uniforms				m_uniforms;

public:
	MeshShader();
	virtual					~MeshShader();

	const Uniforms			GetUniforms() const
	{
		return m_uniforms;
	}

	void					PreRender(CameraPtr pCamera, LightNodePtr pLight);

	inline void				PostRender()
	{
		DeactivateShaderProgram();
	}

	void					AttachAndBuildProgram(const LPWSTR vertexShader = nullptr, const LPWSTR fragmentShader = nullptr);
	void					UpdateUniformValues(const MeshNodePtr pSceneNode) const;
};

