#include "OGLWindow.h"
#include "Resource.h"
#include "GLEW/include/glew.h"
#include "..\Input.h"
#include "..\GLM\gtc\type_ptr.hpp"
#include "../ActorComponent.h"
#include "../TransformComponent.h"
#include "../MaterialComponent.h"
#include "../MeshComponent.h"
#include "../CameraComponent.h"
#include "../SkyBoxComponent.h"

typedef std::shared_ptr<TransformComponent> TransformComponentPtr;
typedef std::shared_ptr<MeshComponent> MeshComponentPtr;
typedef std::shared_ptr<MaterialComponent> MaterialComponentPtr;
typedef std::shared_ptr<CameraComponent> CameraComponentPtr;
typedef std::shared_ptr<SkyBoxComponent> SkyBoxComponenetPtr;

OGLWindow::OGLWindow()
{
}

OGLWindow::~OGLWindow()
{
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

	MeshComponentPtr pMesh;
	CameraComponentPtr pCamera;
	SkyBoxComponenetPtr pSkyBox;
	MaterialComponentPtr pMaterial;
	TransformComponentPtr pTransform;

	// ========== CAMERA START ========== \\

	m_pCamera = std::make_shared<Actor>();

	pTransform = std::make_shared<TransformComponent>();
	pCamera = std::make_shared<CameraComponent>();

	pTransform->SetOwner(m_pCamera);
	pCamera->SetOwner(m_pCamera);

	m_pCamera->AddComponent(pCamera);
	m_pCamera->AddComponent(pTransform);

	m_pCamera->GetComponent<TransformComponent>()->Set(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 0, 0));

	// ========== CAMERA END ========== \\

	// ========== HOUSE START ========== \\

	m_pHouse = std::make_shared<Actor>();

	pTransform = std::make_shared<TransformComponent>();
	pMesh = std::make_shared<MeshComponent>();
	pMaterial = std::make_shared<MaterialComponent>(); 

	pTransform->SetOwner(m_pHouse);
	pMesh->SetOwner(m_pHouse);
	pMaterial->SetOwner(m_pHouse);

	m_pHouse->AddComponent(pTransform);
	m_pHouse->AddComponent(pMesh);
	m_pHouse->AddComponent(pMaterial);

	m_pHouse->GetComponent<TransformComponent>()->Set(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 0, -20));
	m_pHouse->GetComponent<MeshComponent>()->LoadAndBuildMeshFromOBJFile(L"../asset/models/house.obj");
	m_pHouse->GetComponent<MaterialComponent>()->SetDiffuse("../asset/texture/house_diffuse.tga");
	m_pHouse->GetComponent<MaterialComponent>()->SetSpecular("../asset/texture/house_spec.tga");

	// ========== HOUSE END ========== \\

	// ========== SKY BOX START ========== \\

	m_pSkyBox = std::make_shared<Actor>();

	pTransform = std::make_shared<TransformComponent>();
	pSkyBox = std::make_shared<SkyBoxComponent>();

	pTransform->SetOwner(m_pSkyBox);
	pSkyBox->SetOwner(m_pSkyBox);

	m_pSkyBox->AddComponent(pTransform);
	m_pSkyBox->AddComponent(pSkyBox);

	m_pSkyBox->GetComponent<SkyBoxComponent>()->Init("../asset/texture/sky_ft.tga", "../asset/texture/sky_bk.tga", "../asset/texture/sky_lt.tga", "../asset/texture/sky_rt.tga", "../asset/texture/sky_tp.tga", "../asset/texture/sky_bt.tga");
	m_pSkyBox->GetComponent<TransformComponent>()->SetUniformScale(100.0f);

	// ========== SKY BOX END ========== \\

	// ========== ARC 170 START ========== \\

	m_pArc170 = std::make_shared<Actor>();

	pTransform = std::make_shared<TransformComponent>();
	pMesh = std::make_shared<MeshComponent>();
	pMaterial = std::make_shared<MaterialComponent>();

	pTransform->SetOwner(m_pArc170);
	pMesh->SetOwner(m_pArc170);
	pMaterial->SetOwner(m_pArc170);

	m_pArc170->AddComponent(pTransform);
	m_pArc170->AddComponent(pMaterial);
	m_pArc170->AddComponent(pMesh);

	m_pArc170->GetComponent<TransformComponent>()->Set(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 10, -20));
	m_pArc170->GetComponent<TransformComponent>()->SetUniformScale(0.01f);
	m_pArc170->GetComponent<TransformComponent>()->Rotation(180.0f, 0.0f, 0.0f);

	m_pArc170->GetComponent<MeshComponent>()->LoadAndBuildMeshFromOBJFile(L"../asset/models/ARC170.obj");
	m_pArc170->GetComponent<MaterialComponent>()->SetDiffuse("../asset/texture/ARC170_diffuse.tga");

	// ========== ARC 170 END ========== \\
	
	return TRUE;
}

void OGLWindow::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	m_pCamera->GetComponent<CameraComponent>()->Update();

	m_pSkyBox->GetComponent<TransformComponent>()->SetPosition(m_pCamera->GetComponent<TransformComponent>()->GetPosition());

	m_skyBoxShader->ActivateShaderProgram();

	glUniformMatrix4fv(m_uniform_modelview, 1, GL_FALSE, glm::value_ptr(m_pCamera->GetComponent<CameraComponent>()->GetViewMatrixMat4()));
	glUniformMatrix4fv(m_uniform_projection, 1, GL_FALSE, glm::value_ptr(m_pCamera->GetComponent<CameraComponent>()->GetProjectionMat4()));
	glUniformMatrix4fv(m_uniform_local_to_world, 1, GL_FALSE, glm::value_ptr(m_pSkyBox->GetComponent<TransformComponent>()->GetTransformation()));
	glUniform3f(m_uniform_camera_position, 1, GL_FALSE, *glm::value_ptr(m_pCamera->GetComponent<TransformComponent>()->GetPosition()));
	glUniformMatrix4fv(m_uniform_rotation, 1, GL_FALSE, glm::value_ptr(m_pSkyBox->GetComponent<TransformComponent>()->GetOrientation()));

	m_pSkyBox->GetComponent<SkyBoxComponent>()->Render();

	glUniformMatrix4fv(m_uniform_local_to_world, 1, GL_FALSE, glm::value_ptr(m_pArc170->GetComponent<TransformComponent>()->GetTransformation()));
	glUniformMatrix4fv(m_uniform_rotation, 1, GL_FALSE, glm::value_ptr(m_pArc170->GetComponent<TransformComponent>()->GetOrientation()));

	m_pArc170->GetComponent<MeshComponent>()->Render();

	m_skyBoxShader->DeactivateShaderProgram();

	m_shader->ActivateShaderProgram();

	glUniformMatrix4fv(m_uniform_modelview, 1, GL_FALSE, glm::value_ptr(m_pCamera->GetComponent<CameraComponent>()->GetViewMatrixMat4()));
	glUniformMatrix4fv(m_uniform_projection, 1, GL_FALSE, glm::value_ptr(m_pCamera->GetComponent<CameraComponent>()->GetProjectionMat4()));
	glUniformMatrix4fv(m_uniform_local_to_world, 1, GL_FALSE, glm::value_ptr(m_pHouse->GetComponent<TransformComponent>()->GetTransformation()));
	glUniform3f(m_uniform_camera_position, 1, GL_FALSE, *glm::value_ptr(m_pCamera->GetComponent<TransformComponent>()->GetPosition()));
	glUniformMatrix4fv(m_uniform_rotation, 1, GL_FALSE, glm::value_ptr(m_pHouse->GetComponent<TransformComponent>()->GetOrientation()));

	m_pHouse->GetComponent<MeshComponent>()->Render();
	m_pHouse->GetComponent<TransformComponent>()->Rotation(0.2f, 0.0f, 0.0f);

	m_shader->DeactivateShaderProgram();

	SwapBuffers(m_hdc);

	return;
}

void OGLWindow::Resize( int width, int height )
{
	glViewport( 0, 0, width, height );

	m_pCamera->GetComponent<CameraComponent>()._Get()->SetProjection(60.0f, (float)width, (float)height, 1.0f, 1000.0f);
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
}