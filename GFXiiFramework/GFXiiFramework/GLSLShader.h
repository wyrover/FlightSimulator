#ifndef __SHADERGL_H__
#define __SHADERGL_H__
#include <Windows.h>
#include "ShaderBase.h"

class GLSLShader : public ShaderBase
{
	private:
		ShaderProgramHandle			m_ownerProgram;
	public:
									GLSLShader();
		virtual						~GLSLShader();

		virtual EShaderError		CreateShaderFromSourceFile(LPCWSTR filename, EShaderType type);
		virtual void				DeleteShader();
		virtual void				SetShaderOwnerProgram(ShaderProgramHandle handle);
};

class GLSLShaderProgram
{

	private:
		ShaderProgramHandle			m_systemHandle; //handle assigned by opengl;
		ShaderBase*					m_shaders[MAX_NUM_SHADER_PER_PROGRAM];
		int							m_shaderCount;

	public:
									GLSLShaderProgram()
									{
										m_systemHandle = INVALID_SHADER_PROGRAM_HANDLE;
										for(int i = 0; i < MAX_NUM_SHADER_PER_PROGRAM; i++)
										{
											m_shaders[i] = NULL;
										}
										m_shaderCount = 0;
									}
		virtual						~GLSLShaderProgram();

		inline ShaderProgramHandle	GetProgramHandle()
		{
			return m_systemHandle;
		}
		
		void						CreateShaderProgram();
		void						AttachShader(ShaderBase* shader);
		void						AttachAndCompileShaderFromFile(LPCWSTR filename, EShaderType type);
		void						BuildShaderProgram();		
		void						DeleteShaderProgram();
		void						ActivateShaderProgram();
		void						DeactivateShaderProgram();
		void						SetUniform1UInt(unsigned int value, const char* param);
		void						SetAttrib4Float(float f1, float f2, float f3, float f4, const char* param);
		void						BindAttributeLocation( int index, const char* param_name);
};
#endif
