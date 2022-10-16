#include "AppWindow.h"
#include <Windows.h>
#include "InputSystem.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "AGameObject.h"

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::destroy()
{
	if(sharedInstance != NULL)
	{
		sharedInstance->onDestroy();
	}
}

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);
	GraphicsEngine::getInstance()->initialize();
	

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	Renderer::initialize();
	vertexAnim list_anim[] =
	{
		//X - Y - Z
		{Vector3D ( - 0.1f,-0.3f,0.0f),    Vector3D(-0.3f,-0.3f,0.0f),   Vector3D(1,1,0),  Vector3D(0,1,0)}, // POS1
		{Vector3D(-0.1f,0.95f,0.0f),     Vector3D(-0.3f,0.5f,0.0f),   Vector3D(1,1,0),  Vector3D(0,1,1 )},// POS2
		{ Vector3D(0.1f,-0.95f,0.0f),    Vector3D(0.3f,-0.5f,0.0f),   Vector3D(0,1,1),  Vector3D(1,0,0 )},// POS2
		{ Vector3D(0.1f,0.5f,0.0f),      Vector3D(0.3f,0.5f,0.0f),    Vector3D(1,1,1),  Vector3D(0,0,1 )}
		
	};

	//SLIDE 13 CHALLENGE
	vertexAnim list_anim2[] =
	{
		//X - Y - Z
		{Vector3D(-0.78f,-0.8f,0.0f),    Vector3D(-0.78f,-0.8f,0.0f),   Vector3D(0,0,0),  Vector3D(0,1,0) }, // POS1
		{Vector3D(-0.9f,0.08f,0.0f),     Vector3D(-0.9f,0.08f,0.0f),    Vector3D(1,1,0),  Vector3D(0,1,1) }, // POS2
		{ Vector3D(0.1f,-0.2f,0.0f),     Vector3D(0.1f,-0.2f,0.0f),   Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
		{ Vector3D(-0.05f,0.15f,0.0f),     Vector3D(-0.05f,0.15f,0.0f),    Vector3D(1,1,1),  Vector3D(0,0,1) }

	};


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	//GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShaderAnim.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);

	//Renderer::getInstance()->initializeQuadsAnim(list_anim2, shader_byte_code, size_shader);
	//Renderer::getInstance()->initializeQuadsAnim(list_anim2, shader_byte_code, size_shader);
	//Renderer::getInstance()->initializeQuadsAnim(list_anim3, shader_byte_code, size_shader);
	//Renderer::getInstance()->initializeQuads(list2, shader_byte_code, size_shader);
	//Renderer::getInstance()->initializeQuads(list3, shader_byte_code, size_shader);

	for (int i = 0; i < 100; i++) {
		//Renderer::getInstance()->initializeCube(shader_byte_code, size_shader);
		//std::cout << "hello world" << std::endl;
	}
	Renderer::getInstance()->initializeCube(shader_byte_code, size_shader, 1);
	Renderer::getInstance()->initializeCube(shader_byte_code, size_shader, 0);
	

	GraphicsEngine::getInstance()->releaseCompiledShader();

	//GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShaderAnim.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	//Renderer::getInstance()->initializeQuadConst();
	Renderer::getInstance()->initializeCubeConst();
	/*
	constant cc;
	cc.m_angle = 0;
	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
	*/
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::getInstance()->update();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,0.3, 0.3, 0.3, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	cc.m_world.setIdentity();
	Matrix4x4 temp;
	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;


	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;


	world_cam.inverse();




	cc.m_view = world_cam;
	/*cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/300.0f,
		-4.0f,
		4.0f
	);*/

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);


	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);


	for (auto const& i : Renderer::getInstance()->getQuadList()) {
		i->draw(m_vs, m_ps);
	}

	for (auto const& i : Renderer::getInstance()->getCubeList()) {
		i->draw(m_vs, m_ps);
	}


	
	m_swap_chain->present(true);

	/*
	 FOR ANIMATION - PART 9
	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += 1.57f * m_delta_time;
	constant cc;
	cc.m_angle = m_angle;
	
	
	
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	*/

	
	
	/*
	 //SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);
	
	 IN QUADS DRAW FUNC
	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	*/
	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	InputSystem::destroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	//Renderer::destroy();
	GraphicsEngine::getInstance()->release();

}

void AppWindow::onFocus()
{
	Window::onFocus();
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	Window::onKillFocus();
	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		m_rot_x += 3.14f * EngineTime::getDeltaTime();
	}
	else if (key == 'S')
	{
		m_rot_x -= 3.14f * EngineTime::getDeltaTime();
	}
	else if (key == 'A')
	{
		m_rot_y += 3.14f * EngineTime::getDeltaTime();
	}
	else if (key == 'D')
	{
		m_rot_y -= 3.14f * EngineTime::getDeltaTime();
	}
}

void AppWindow::onKeyUp(int key)
{

}

void AppWindow::onMouseMove(const Point& delta_mouse_pos)
{
	m_rot_x -= delta_mouse_pos.m_y * EngineTime::getDeltaTime();
	m_rot_y -= delta_mouse_pos.m_x * EngineTime::getDeltaTime();
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}
