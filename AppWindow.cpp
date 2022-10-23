#include "AppWindow.h"
#include <Windows.h>
#include "InputSystem.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "UISystem.h"

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
	InputSystem::get()->addListener(this);
	GraphicsEngine::getInstance()->initialize();
	
	UISystem::getInstance()->initialize();
	UISystem::getInstance()->initImGUI(this->m_hwnd);

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	m_world_cam.setTranslation(Vector3D(0, 0, -2));

	Renderer::initialize();

	GraphicsEngine::getInstance()->createRenderTexture(rc.right - rc.left, rc.bottom - rc.top);
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
		{Vector3D(-0.78f,-0.8f,0.0f),    Vector3D(-0.32f,-0.11f,0.0f),   Vector3D(0,0,0),  Vector3D(0,1,0) }, // POS1
		{Vector3D(-0.9f,0.08f,0.0f),     Vector3D(-0.11f,0.78f,0.0f),    Vector3D(1,1,0),  Vector3D(0,1,1) }, // POS2
		{ Vector3D(0.1f,-0.2f,0.0f),     Vector3D(0.75f,-0.73f,0.0f),   Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
		{ Vector3D(-0.05f,0.15f,0.0f),      Vector3D(0.88f,0.77f,0.0f),    Vector3D(1,1,1),  Vector3D(0,0,1) }

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
	Renderer::getInstance()->initializeCube(shader_byte_code, size_shader, 0);
	Renderer::getInstance()->initializeCube(shader_byte_code, size_shader, 1);

	GraphicsEngine::getInstance()->releaseCompiledShader();

	//GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShaderAnim.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	//Renderer::getInstance()->initializeQuadConst();
	Renderer::getInstance()->initializeCubeConst();
	
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();

	GraphicsEngine::getInstance()->RenderToTexture(this->m_swap_chain);
	//Render Everything
	for (auto const& i : Renderer::getInstance()->getQuadList()) {
		i->draw(m_vs, m_ps);
	}

	for (auto const& i : Renderer::getInstance()->getCubeList()) {
		i->draw(m_vs, m_ps);
	}

	GraphicsEngine::getInstance()->SetBackBufferRenderTarget(this->m_swap_chain);

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,0.3, 0.3, 0.3, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	UISystem::getInstance()->updateNewFrame();

	for (auto const& i : Renderer::getInstance()->getQuadList()) {
		i->draw(m_vs, m_ps);
	}

	for (auto const& i : Renderer::getInstance()->getCubeList()) {
		i->draw(m_vs, m_ps);
	}

	UISystem::getInstance()->update(this->m_swap_chain);

	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::getInstance()->release();
	UISystem::getInstance()->destroy();

}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		//m_rot_x += 3.14f*m_delta_time;
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//m_rot_x -= 3.14f*m_delta_time;
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		//m_rot_y += 3.14f*m_delta_time;
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 3.14f*m_delta_time;
		m_rightward = 1.0f;
	}
}

void AppWindow::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);



	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.5f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.5f;



	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));


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