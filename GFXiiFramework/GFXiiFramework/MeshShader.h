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
		int modelview, projection, localToWorld, cameraPosition, rotation, bCalculateSpecular, bCalculateNormal, dayAndNight;
	};

	Uniforms				m_uniforms;

public:
	MeshShader();
	virtual					~MeshShader();

	const Uniforms			GetUniforms() const
	{
		return m_uniforms;
	}

	void					PreRender(CameraPtr pCamera, glm::vec4& dayAndNight);

	inline void				PostRender()
	{
		DeactivateShaderProgram();
	}

	void					AttachAndBuildProgram(const LPWSTR vertexShader, const LPWSTR fragmentShader);
	void					UpdateUniformValues(const MeshNodePtr pSceneNode) const;
};

