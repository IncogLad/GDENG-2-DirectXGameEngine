#include "AppWindow.h"
#include <Windows.h>

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
	GraphicsEngine::getInstance()->initialize();

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	Renderer::initialize();
	vertex list1[] =
	{
		//X - Y - Z
		/*
		{-0.3f,-0.3f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0}, // POS1
		{-0.3f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 },// POS2
		{ 0.3f,-0.5f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS2
		{ 0.3f,0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
		*/
		{-0.1f,-0.3f,0.0f,   1,1,0}, // POS1
		{-0.1f,0.95f,0.0f,    1,0,0}, // POS2
		{ 0.1f,-0.95f,0.0f,   0,0,1}, // POS3
		{ 0.1f,0.5f,0.0f,    0,1,0.4f}
	};

	vertex list2[] =
	{
		{-0.9f,-0.9f,0.0f,   1,0,0}, // POS1
		{-0.9f,0.9f,0.0f,    0,1,0}, // POS2
		{ -0.3f,-0.9f,0.0f,   0,0,1}, // POS3
		{ -0.3f,0.9f,0.0f,    1,1,0}
	};

	vertex list3[] =
	{
		{0.3f,-0.6f,0.0f,   1,1,0}, 
		{0.3f,0.7f,0.0f,    0,1,1}, 
		{ 0.6f,-0.9f,0.0f,   0,0,1}, 
		{ 0.9f,0.8f,0.0f,    1,0.3f,0.4f}
	};

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);

	Renderer::getInstance()->initializeQuads(list1, shader_byte_code, size_shader);
	Renderer::getInstance()->initializeQuads(list2, shader_byte_code, size_shader);
	Renderer::getInstance()->initializeQuads(list3, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();


	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

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
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	for (auto const& i : Renderer::getInstance()->getQuadList()) {
		i->draw();
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
	
	Renderer::getInstance()->getQuadList().back()->draw(m_vs, m_ps);
	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	*/

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	
	/*
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
	//m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();

	//Renderer::destroy();

	GraphicsEngine::getInstance()->release();

}

