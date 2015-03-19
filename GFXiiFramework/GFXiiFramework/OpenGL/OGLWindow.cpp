#include "OGLWindow.h"
#include "Resource.h"
#include "GLEW/include/glew.h"
#include <iostream>

OGLWindow::OGLWindow()
{
	m_euler[0] = m_euler[1] = m_euler[2] = 0.0f;
}

OGLWindow::~OGLWindow()
{
	//Clean up the renderable
	delete m_mesh;
	delete m_shader;

	DestroyOGLContext();
}

OGLWindow::OGLWindow(HINSTANCE hInstance, int width, int height)
{
	m_euler[0] = m_euler[1] = m_euler[2] = 0.0f;
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

	glDeleteSamplers( 1, (GLuint*)(&m_texDefaultSampler) );

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
	m_hwnd = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, L"RenderWindow", L"OGLWindow", WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0, 0, width, height, NULL, NULL, hInstance, NULL);

	if ( ! m_hwnd )
		return FALSE;

	m_hdc = GetDC( m_hwnd );

	if ( !(m_hglrc = CreateOGLContext( m_hdc )) )
		return FALSE;

	glewInit();

	InitOGLState();

	m_width = width;
	m_height = height;
	
	m_mesh = new OGLMesh(L"../asset/models/house.obj");

	m_texture = new OGLTexture();
	m_texture->CreateTextureFromFile( "../asset/texture/house_diffuse.tga");

	m_mesh->SetTexture( m_texture );

	return TRUE;
}

void OGLWindow::Render()
{
	float modelview[16] = { 0 };
	float projection[16] = { 0 };

	Renderable* prenderable = static_cast<Renderable*>(m_mesh);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	m_camera.GetModelView(modelview);
	m_camera.GetProjection(projection);

	glUniformMatrix4fv( m_uniform_modelview, 1, GL_FALSE, modelview );
	glUniformMatrix4fv( m_uniform_projection, 1, GL_FALSE, projection );
	
	glBindSampler(0, m_texDefaultSampler);

	prenderable->Render();

	SwapBuffers(m_hdc);

	return;
}

void OGLWindow::Resize( int width, int height )
{
	glViewport(0, 0, width, height);

	m_camera.SetProjectionMatrix(60.f, (float)width / (float)height, 1.f, 1000.f);

	return;
}

void OGLWindow::InitOGLState()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//Initialise OGL shader
	m_shader = new OGLShaderProgram();

	m_shader->CreateShaderProgram();
	m_shader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/basic.vert", SHADER_VERTEX);
	m_shader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/basic.frag", SHADER_FRAGMENT);

	//m_shader->BindAttributeLocation( 0, "position" );
	//m_shader->BindAttributeLocation( 1, "inNormal" );
	//m_shader->BindAttributeLocation( 2, "inUV" );

	glBindFragDataLocation( m_shader->GetProgramHandle(), 0, "outFrag" );

	m_shader->BuildShaderProgram();
	m_shader->ActivateShaderProgram();

	m_uniform_modelview = glGetUniformLocation(m_shader->GetProgramHandle(), "modelview");
	m_uniform_projection = glGetUniformLocation(m_shader->GetProgramHandle(), "projection");
	m_uniform_texture = glGetUniformLocation(m_shader->GetProgramHandle(), "texColour");

	glUniform1i( m_uniform_texture, 0 );

	//Create a texture sampler
	glGenSamplers( 1, (GLuint*)(&m_texDefaultSampler) );
	
	glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_MIN_FILTER , GL_LINEAR);  
	glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_MAG_FILTER , GL_LINEAR);


	m_camera.SetCameraPosition(&glm::vec3(0, 0, 10));
	m_camera.SetLookAtPoint(&glm::vec3(0, 0, 0));
}


// ===== INPUT ===== \\

BOOL OGLWindow::MouseLBDown (int x, int y)
{
	m_camera.MouseDown();

	return TRUE;
}

BOOL OGLWindow::MouseLBUp (int x, int y)
{
	m_camera.MouseUp();

	return TRUE;
}

BOOL OGLWindow::MouseMove (int x, int y)
{
	m_camera.MouseMove(x, y);

	return TRUE;
}

BOOL OGLWindow::MouseWheel(int val)
{
	val > 0 ? m_camera.ZoomCamera(-1) : m_camera.ZoomCamera(1);

	return TRUE;
}

BOOL OGLWindow::KeyPressS()
{
	m_camera.DollyCamera(0.1f);

	return TRUE;
}

BOOL OGLWindow::KeyPressW()
{
	m_camera.DollyCamera(-0.1f);

	return TRUE;
}

BOOL OGLWindow::KeyPressA()
{
	m_camera.StrafeCamera(-0.1f);

	return TRUE;
}

BOOL OGLWindow::KeyPressD()
{
	m_camera.StrafeCamera(0.1f);

	return TRUE;
}

BOOL OGLWindow::KeyPressX()
{
	m_camera.PedCamera(0.1f);

	return TRUE;
}

BOOL OGLWindow::KeyPressZ()
{
	m_camera.PedCamera(-0.1f);

	return TRUE;
}

BOOL OGLWindow::KeyPressQ()
{
	m_camera.RotateCamera(0, 0, -1.f);

	return TRUE;
}

BOOL OGLWindow::KeyPressE()
{
	m_camera.RotateCamera(0, 0, 1.f);

	return TRUE;
}