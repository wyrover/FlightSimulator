#include "OGLWindow.h"
#include "Resource.h"
#include "GLEW/include/glew.h"
#include "..\Input.h"
#include "..\GLM\gtc\type_ptr.hpp"

OGLWindow::OGLWindow()
{
}

OGLWindow::~OGLWindow()
{
	//Clean up the GameObject
	delete m_house;
	delete m_aircraft;
	delete m_camera;
	delete m_shader;

	DestroyOGLContext();
}

HGLRC OGLWindow::CreateOGLContext(HDC hdc)
{
	unsigned int pixelformat;
	HGLRC hglrc;

	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Support Window
		PFD_SUPPORT_OPENGL |						// Format Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request RGBA Format
		32,											// Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits mask
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// Z-Buffer depth
		0,											// Stencil Buffer
		0,											// Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(pixelformat=ChoosePixelFormat(hdc,&pfd)))
	{
		return 0;
	}

	if(!SetPixelFormat(hdc,pixelformat,&pfd))
	{
		return 0;
	}

	if (!(hglrc=wglCreateContext(hdc)))
	{
		return 0;
	}

	if(!wglMakeCurrent(hdc,hglrc))
	{
		return 0;
	}

	return hglrc;
}

void OGLWindow::DestroyRenderWindow()
{
	DestroyWindow( m_hwnd );

	m_hwnd = NULL;
	m_hdc = NULL;
}

BOOL OGLWindow::DestroyOGLContext()
{
	//glDeleteSamplers( 1, (GLuint*)(&m_texDefaultSampler) );

	if ( m_hglrc )
	{
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( m_hglrc );
		m_hglrc = NULL;
	}
	
	if ( !ReleaseDC ( m_hwnd, m_hdc ) )
		return FALSE;

	return TRUE;
}

BOOL OGLWindow::InitWindow(HINSTANCE hInstance, int width, int height)
{
	m_hwnd = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		L"RenderWindow", L"OGLWindow", WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
		0, 0, width, height, NULL, NULL, hInstance, NULL);

	if ( ! m_hwnd )
		return FALSE;

	m_hdc = GetDC( m_hwnd );

	if ( !(m_hglrc = CreateOGLContext( m_hdc )) )
		return FALSE;

	glewInit();

	InitOGLState();

	m_width = width;
	m_height = height;

	//m_camera = new OGLCamera();
	//m_skyBox = new OGLSkyBox();
	//m_house = new OGLMesh(L"../asset/models/house.obj", "../asset/texture/house_diffuse.tga", "../asset/texture/house_spec.tga");
	//m_aircraft = new OGLMesh(L"../asset/models/ARC170.obj", "../asset/texture/ARC170_diffuse.tga");

	//m_camera->Set(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 5, 0));
	//m_house->Set(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0), glm::vec3(0, 0, 1), glm::vec3(1, 2, -20));
	//m_aircraft->Set(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 0, -10));

	//m_skyBox->Init("../asset/texture/sky_ft.tga", "../asset/texture/sky_bk.tga", "../asset/texture/sky_lt.tga", "../asset/texture/sky_rt.tga", "../asset/texture/sky_tp.tga", "../asset/texture/sky_bt.tga");
	//m_skyBox->SetUniformScale(100.0f);

	//m_aircraft->Rotation(180.0f, 0.0f, 0.0f);
	//m_aircraft->SetUniformScale(0.01f);

	//Player::Get().SetCamera(m_camera);
	//Player::Get().SetCurrentGameObject(m_aircraft);
	
	return TRUE;
}

void OGLWindow::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//Player::Get().Update();

	//m_camera->Update();
	//m_skyBox->SetPosition(m_camera->GetPosition());

	//m_skyBoxShader->ActivateShaderProgram();

	//glUniformMatrix4fv(m_uniform_modelview, 1, GL_FALSE, glm::value_ptr(Player::Get().GetCamera()->GetViewMatrixMat4()));
	//glUniformMatrix4fv(m_uniform_projection, 1, GL_FALSE, glm::value_ptr(Player::Get().GetCamera()->GetProjectionMat4()));
	//glUniformMatrix4fv(m_uniform_local_to_world, 1, GL_FALSE, glm::value_ptr(m_skyBox->GetTransformation()));
	//glUniform3f(m_uniform_camera_position, 1, GL_FALSE, *glm::value_ptr(Player::Get().GetCamera()->GetPosition()));
	//glUniformMatrix4fv(m_uniform_rotation, 1, GL_FALSE, glm::value_ptr(m_skyBox->GetOrientation()));

	//m_skyBox->Render();

	//m_aircraft->Render();

	m_skyBoxShader->DeactivateShaderProgram();

	m_shader->ActivateShaderProgram();

	//glUniformMatrix4fv(m_uniform_modelview, 1, GL_FALSE, glm::value_ptr(Player::Get().GetCamera()->GetViewMatrixMat4()));
	//glUniformMatrix4fv(m_uniform_projection, 1, GL_FALSE, glm::value_ptr(Player::Get().GetCamera()->GetProjectionMat4()));
	//glUniformMatrix4fv(m_uniform_local_to_world, 1, GL_FALSE, glm::value_ptr(m_house->GetTransformation()));
	//glUniform3f(m_uniform_camera_position, 1, GL_FALSE, *glm::value_ptr(Player::Get().GetCamera()->GetPosition()));
	//glUniformMatrix4fv(m_uniform_rotation, 1, GL_FALSE, glm::value_ptr(m_house->GetOrientation()));
	
	//glBindSampler(0, m_texDefaultSampler); ??

	//m_house->Render();

	//m_house->Rotation(0.2f, 0.0f, 0.0f);


	m_shader->DeactivateShaderProgram();

	SwapBuffers(m_hdc);

	return;
}

void OGLWindow::Resize( int width, int height )
{
	glViewport( 0, 0, width, height );
	//m_camera->SetProjection(60.0f, (float)width, (float)height, 1.0f, 1000.0f);
}

void OGLWindow::InitOGLState()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// ========== Standard shader ========== \\

	m_shader = new OGLShaderProgram();

	m_shader->CreateShaderProgram();
	m_shader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/standard.vert", SHADER_VERTEX);
	m_shader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/standard.frag", SHADER_FRAGMENT);

	glBindFragDataLocation(m_shader->GetProgramHandle(), 0, "outFrag");

	m_shader->BuildShaderProgram();
	//m_shader->ActivateShaderProgram();

	m_uniform_modelview = glGetUniformLocation(m_shader->GetProgramHandle(), "modelview");
	m_uniform_projection = glGetUniformLocation(m_shader->GetProgramHandle(), "projection");
	m_uniform_local_to_world = glGetUniformLocation(m_shader->GetProgramHandle(), "localToWorld");
	m_uniform_camera_position = glGetUniformLocation(m_shader->GetProgramHandle(), "cameraPosition");
	m_uniform_rotation = glGetUniformLocation(m_shader->GetProgramHandle(), "rotation");

	// ========== Sky box shader ========== \\

	m_skyBoxShader = new OGLShaderProgram();

	m_skyBoxShader->CreateShaderProgram();
	m_skyBoxShader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/skybox.vert", SHADER_VERTEX);
	m_skyBoxShader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/skybox.frag", SHADER_FRAGMENT);

	glBindFragDataLocation(m_skyBoxShader->GetProgramHandle(), 0, "outFrag");

	m_skyBoxShader->BuildShaderProgram();
	//m_skyBoxShader->ActivateShaderProgram();

	// ========== ???? ========== \\

	//m_uniform_texture = glGetUniformLocation(m_shader->GetProgramHandle(), "texColour");

	//glUniform1i( m_uniform_texture, 0 );

	////Create a texture sampler
	//glGenSamplers( 1, (GLuint*)(&m_texDefaultSampler) );
	//
	//glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	//glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	//glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_MIN_FILTER , GL_LINEAR);  
	//glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
}