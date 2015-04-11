#include "ApplicationWindow.h"
#include "Resource.h"
#include "GLEW/include/glew.h"
#include "Input.h"
#include "glm/gtc/type_ptr.hpp"
#include "ActorComponent.h"
#include "TransformComponent.h"
#include "MaterialComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "SkyBoxComponent.h"
#include "RootNode.h"
#include "ShaderComponent.h"
#include "SkyBoxNode.h"

typedef std::shared_ptr<TransformComponent> TransformComponentPtr;
typedef std::shared_ptr<MeshComponent> MeshComponentPtr;
typedef std::shared_ptr<MaterialComponent> MaterialComponentPtr;
typedef std::shared_ptr<CameraComponent> CameraComponentPtr;
typedef std::shared_ptr<SkyBoxComponent> SkyBoxComponenetPtr;

ApplicationWindow::ApplicationWindow()
{
}

ApplicationWindow::~ApplicationWindow()
{
	DestroyOGLContext();
}

HGLRC ApplicationWindow::CreateOGLContext(HDC hdc)
{
	unsigned int pixelformat;
	HGLRC hglrc;

	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Support ApplicationWindow
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

void ApplicationWindow::DestroyRenderWindow()
{
	DestroyWindow( m_hwnd );

	m_hwnd = NULL;
	m_hdc = NULL;
}

BOOL ApplicationWindow::DestroyOGLContext()
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

BOOL ApplicationWindow::InitWindow(HINSTANCE hInstance, int width, int height)
{
	m_hwnd = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		L"RenderWindow", L"ApplicationWindow", WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
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
	
	return TRUE;
}

void ApplicationWindow::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	m_pCamera->GetComponent<CameraComponent>()->Update();
	m_pSkyBox->GetComponent<TransformComponent>()->SetPosition(m_pCamera->GetComponent<TransformComponent>()->GetPosition());

	m_scene.Render();

	m_pHouse->GetComponent<TransformComponent>()->Rotation(0.2f, 0.0f, 0.0f);

	SwapBuffers(m_hdc);

	return;
}

void ApplicationWindow::Resize( int width, int height )
{
	glViewport( 0, 0, width, height );

	m_pCamera->GetComponent<CameraComponent>()._Get()->SetProjection(60.0f, (float)width, (float)height, 1.0f, 1000.0f);
}

void ApplicationWindow::InitOGLState()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	MeshComponentPtr pMesh;
	CameraComponentPtr pCamera;
	SkyBoxComponenetPtr pSkyBox;
	MaterialComponentPtr pMaterial;
	TransformComponentPtr pTransform;
	ShaderComponentPtr pShader;

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
	pShader = std::make_shared<ShaderComponent>();

	pTransform->SetOwner(m_pHouse);
	pMesh->SetOwner(m_pHouse);
	pMaterial->SetOwner(m_pHouse);
	pShader->SetOwner(m_pHouse);

	m_pHouse->AddComponent(pTransform);
	m_pHouse->AddComponent(pMesh);
	m_pHouse->AddComponent(pMaterial);
	m_pHouse->AddComponent(pShader);

	m_pHouse->GetComponent<TransformComponent>()->Set(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 0, -20));
	m_pHouse->GetComponent<MeshComponent>()->LoadAndBuildMeshFromOBJFile(L"../asset/models/house.obj");
	m_pHouse->GetComponent<MaterialComponent>()->SetDiffuse("../asset/texture/house_diffuse.tga");
	m_pHouse->GetComponent<MaterialComponent>()->SetSpecular("../asset/texture/house_spec.tga");

	m_pHouse->GetComponent<ShaderComponent>()->SetCamera(pCamera);
	m_pHouse->GetComponent<ShaderComponent>()->AddFragmentShader(L"../asset/shader/glsl/standard.frag");
	m_pHouse->GetComponent<ShaderComponent>()->AddVertexShader(L"../asset/shader/glsl/standard.vert");
	m_pHouse->GetComponent<ShaderComponent>()->BuildShaderProgram();

	// ========== HOUSE END ========== \\

	// ========== SKY BOX START ========== \\

	m_pSkyBox = std::make_shared<Actor>();

	pTransform = std::make_shared<TransformComponent>();
	pSkyBox = std::make_shared<SkyBoxComponent>();
	pShader = std::make_shared<ShaderComponent>();

	pTransform->SetOwner(m_pSkyBox);
	pSkyBox->SetOwner(m_pSkyBox);
	pShader->SetOwner(m_pSkyBox);

	m_pSkyBox->AddComponent(pTransform);
	m_pSkyBox->AddComponent(pSkyBox);
	m_pSkyBox->AddComponent(pShader);

	m_pSkyBox->GetComponent<SkyBoxComponent>()->Init("../asset/texture/sky_ft.tga", "../asset/texture/sky_bk.tga", "../asset/texture/sky_lt.tga", "../asset/texture/sky_rt.tga", "../asset/texture/sky_tp.tga", "../asset/texture/sky_bt.tga");
	m_pSkyBox->GetComponent<TransformComponent>()->SetUniformScale(100.0f);

	m_pSkyBox->GetComponent<ShaderComponent>()->SetCamera(pCamera);
	m_pSkyBox->GetComponent<ShaderComponent>()->AddFragmentShader(L"../asset/shader/glsl/skybox.frag");
	m_pSkyBox->GetComponent<ShaderComponent>()->AddVertexShader(L"../asset/shader/glsl/skybox.vert");
	m_pSkyBox->GetComponent<ShaderComponent>()->BuildShaderProgram();

	// ========== SKY BOX END ========== \\

	// ========== ARC 170 START ========== \\

	m_pArc170 = std::make_shared<Actor>();

	pTransform = std::make_shared<TransformComponent>();
	pMesh = std::make_shared<MeshComponent>();
	pMaterial = std::make_shared<MaterialComponent>();
	pShader = std::make_shared<ShaderComponent>();

	pTransform->SetOwner(m_pArc170);
	pMesh->SetOwner(m_pArc170);
	pMaterial->SetOwner(m_pArc170);
	pShader->SetOwner(m_pArc170);

	m_pArc170->AddComponent(pTransform);
	m_pArc170->AddComponent(pMaterial);
	m_pArc170->AddComponent(pMesh);
	m_pArc170->AddComponent(pShader);

	m_pArc170->GetComponent<TransformComponent>()->Set(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 10, -20));
	m_pArc170->GetComponent<TransformComponent>()->SetUniformScale(0.01f);
	m_pArc170->GetComponent<TransformComponent>()->Rotation(180.0f, 0.0f, 0.0f);

	m_pArc170->GetComponent<MeshComponent>()->LoadAndBuildMeshFromOBJFile(L"../asset/models/ARC170.obj");
	m_pArc170->GetComponent<MaterialComponent>()->SetDiffuse("../asset/texture/ARC170_diffuse.tga");

	m_pArc170->GetComponent<ShaderComponent>()->SetCamera(pCamera);
	m_pArc170->GetComponent<ShaderComponent>()->AddFragmentShader(L"../asset/shader/glsl/skybox.frag");
	m_pArc170->GetComponent<ShaderComponent>()->AddVertexShader(L"../asset/shader/glsl/skybox.vert");
	m_pArc170->GetComponent<ShaderComponent>()->BuildShaderProgram();

	// ========== ARC 170 END ========== \\

	SceneNodePtr pRoot = std::make_shared<RootNode>();
	SceneNodePtr pHouseNode = std::make_shared<MeshNode>(m_pHouse);
	SceneNodePtr pArc170 = std::make_shared<MeshNode>(m_pArc170);
	SceneNodePtr pSky = std::make_shared<SkyBoxNode>(m_pSkyBox);

	pRoot->AddChild(pSky);
	pRoot->AddChild(pHouseNode);
	pRoot->AddChild(pArc170);

	m_scene.SetRoot(pRoot);
}