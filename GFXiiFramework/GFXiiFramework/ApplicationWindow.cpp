#include "ApplicationWindow.h"
#include "Resource.h"
#include "GLEW/include/glew.h"
#include "Input.h"
#include "glm/gtc/type_ptr.hpp"
#include "ActorComponent.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Camera.h"
#include "SkyBox.h"
#include "RootNode.h"
#include "Shader.h"
#include "SkyBoxNode.h"
#include "CharacterController.h"

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

	m_pScene->Render();

	m_pHouse->GetComponent<Transform>()->Rotation(0.2f, 0.0f, 0.0f);

	SwapBuffers(m_hdc);

	return;
}

void ApplicationWindow::Resize( int width, int height )
{
	glViewport( 0, 0, width, height );

	m_pScene->GetCamera()->SetProjection(60.0f, (float)width, (float)height, 1.0f, 1000.0f);
}

void ApplicationWindow::InitOGLState()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	XMLReader reader;

	reader.ReadFile("testing.xml");

	ActorFactory actorFactory;
	ScenePtr pTestScene;

	actorFactory.CreateActorsFromDOM(reader.GetDOM());

	//MeshPtr pMesh;
	//CameraPtr pCamera;
	//SkyBoxPtr pSkyBox;
	//MaterialPtr pMaterial;
	//TransformPtr pTransform;
	//ShaderPtr pShader;
	//CharacterControllerPtr pCharacter;

	//// ========== SHADER START ========== \\

	//ShaderProgramPtr pStandardShader, pSkyBoxShader;

	//pStandardShader = std::make_shared<GLSLShaderProgram>();

	//pStandardShader->CreateShaderProgram();
	//pStandardShader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/standard.frag", EShaderType::SHADER_FRAGMENT);
	//pStandardShader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/standard.vert", EShaderType::SHADER_VERTEX);
	//
	//glBindFragDataLocation(pStandardShader->GetProgramHandle(), 0, "outfrag");

	//pStandardShader->BuildShaderProgram();

	//pSkyBoxShader = std::make_shared<GLSLShaderProgram>();

	//pSkyBoxShader->CreateShaderProgram();
	//pSkyBoxShader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/skybox.frag", EShaderType::SHADER_FRAGMENT);
	//pSkyBoxShader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/skybox.vert", EShaderType::SHADER_VERTEX);

	//glBindFragDataLocation(pSkyBoxShader->GetProgramHandle(), 0, "outfrag");

	//pSkyBoxShader->BuildShaderProgram();

	//// ========== SHADER END ========== \\

	//// ========== ARC 170 START ========== \\

	//m_pArc170 = std::make_shared<Actor>(0);

	//pCharacter = std::make_shared<CharacterController>();
	//pCamera = std::make_shared<Camera>();
	//pTransform = std::make_shared<Transform>();
	//pMesh = std::make_shared<Mesh>();
	//pMaterial = std::make_shared<Material>();
	//pShader = std::make_shared<Shader>(pStandardShader);

	//pTransform->SetOwner(m_pArc170);
	//pMesh->SetOwner(m_pArc170);
	//pMaterial->SetOwner(m_pArc170);
	//pShader->SetOwner(m_pArc170);
	//pCharacter->SetOwner(m_pArc170);
	//pCamera->SetOwner(m_pArc170);

	//m_pArc170->AddComponent(pTransform);
	//m_pArc170->AddComponent(pMaterial);
	//m_pArc170->AddComponent(pMesh);
	//m_pArc170->AddComponent(pShader);
	//m_pArc170->AddComponent(pCharacter);
	//m_pArc170->AddComponent(pCamera);

	//m_pArc170->GetComponent<Transform>()->Set(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, -10, -20));
	//m_pArc170->GetComponent<Transform>()->SetUniformScale(0.01f);
	//m_pArc170->GetComponent<Transform>()->Rotation(180.0f, 0.0f, 0.0f);

	//m_pArc170->GetComponent<Mesh>()->LoadAndBuildMeshFromOBJFile(L"../asset/models/ARC170.obj");
	//m_pArc170->GetComponent<Material>()->SetDiffuse("../asset/texture/ARC170_diffuse.tga");
	//m_pArc170->GetComponent<Shader>()->SetCamera(pCamera);

	//// ========== ARC 170 END ========== \\

	//// ========== HOUSE START ========== \\

	//m_pHouse = std::make_shared<Actor>(1);

	//pTransform = std::make_shared<Transform>();
	//pMesh = std::make_shared<Mesh>();
	//pMaterial = std::make_shared<Material>();
	//pShader = std::make_shared<Shader>(pStandardShader);

	//pTransform->SetOwner(m_pHouse);
	//pMesh->SetOwner(m_pHouse);
	//pMaterial->SetOwner(m_pHouse);
	//pShader->SetOwner(m_pHouse);

	//m_pHouse->AddComponent(pTransform);
	//m_pHouse->AddComponent(pMesh);
	//m_pHouse->AddComponent(pMaterial);
	//m_pHouse->AddComponent(pShader);

	//m_pHouse->GetComponent<Transform>()->Set(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 0, -20));
	//m_pHouse->GetComponent<Mesh>()->LoadAndBuildMeshFromOBJFile(L"../asset/models/house.obj");
	//m_pHouse->GetComponent<Material>()->SetDiffuse("../asset/texture/house_diffuse.tga");
	//m_pHouse->GetComponent<Material>()->SetSpecular("../asset/texture/house_spec.tga");
	//m_pHouse->GetComponent<Shader>()->SetCamera(pCamera);
	//m_pHouse->GetComponent<Shader>()->SetCalculateSpecular(true);

	//// ========== HOUSE END ========== \\

	//// ========== SKY BOX START ========== \\

	//m_pSkyBox = std::make_shared<Actor>(2);

	//pTransform = std::make_shared<Transform>();
	//pSkyBox = std::make_shared<SkyBox>();
	//pShader = std::make_shared<Shader>(pSkyBoxShader);

	//pTransform->SetOwner(m_pSkyBox);
	//pSkyBox->SetOwner(m_pSkyBox);
	//pShader->SetOwner(m_pSkyBox);

	//m_pSkyBox->AddComponent(pTransform);
	//m_pSkyBox->AddComponent(pSkyBox);
	//m_pSkyBox->AddComponent(pShader);

	//m_pSkyBox->GetComponent<SkyBox>()->Init("../asset/texture/sky_ft.tga", "../asset/texture/sky_bk.tga", "../asset/texture/sky_lt.tga", "../asset/texture/sky_rt.tga", "../asset/texture/sky_tp.tga", "../asset/texture/sky_bt.tga");
	//m_pSkyBox->GetComponent<Transform>()->SetUniformScale(100.0f);
	//m_pSkyBox->GetComponent<Shader>()->SetCamera(pCamera);

	//// ========== SKY BOX END ========== \\

	//SceneNodePtr pRoot = std::make_shared<RootNode>();
	//SceneNodePtr pHouseNode = std::make_shared<MeshNode>(m_pHouse);
	//SceneNodePtr pArc170 = std::make_shared<MeshNode>(m_pArc170);
	//SceneNodePtr pSky = std::make_shared<SkyBoxNode>(m_pSkyBox);

	//pRoot->AddChild(pHouseNode);
	//pRoot->AddChild(pArc170);

	//m_pScene = std::make_shared<Scene>();

	//m_pScene->SetRoot(pRoot);
	//m_pScene->SetCamera(m_pArc170->GetComponent<Camera>());
	//m_pScene->SetSkyBox(pSkyBox);
	//m_pScene->SetCharacterController(m_pArc170->GetComponent<CharacterController>());
}