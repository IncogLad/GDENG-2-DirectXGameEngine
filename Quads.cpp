#include "Quads.h"
#include "EngineTime.h"


Quads::Quads()
{
}

Quads::~Quads()
{
}

void Quads::initialize()
{
	AGameObject::initialize();
}

void Quads::destroy()
{
	AGameObject::destroy();
}

void Quads::initBuffers(vertex list[], void* shader_byte_code, size_t size_shader)
{
	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(list);
	std::cout << list->position.x << std::endl;
	m_vb->load(list, sizeof(vertex), 4, shader_byte_code, size_shader);
}

void Quads::initAnimBuffers(vertexAnim listAnim[], void* shader_byte_code, size_t size_shader)
{
	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(list);
	std::cout << listAnim->position.x << std::endl;
	m_vb->load(listAnim, sizeof(vertexAnim), 4, shader_byte_code, size_shader);
}

void Quads::initConstBuffers()
{
	cc.m_angle = 0.0f;
	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Quads::draw(VertexShader* m_vs, PixelShader* m_ps)
{
	cc.m_angle += static_cast<float>(speed * EngineTime::getDeltaTime());
	if (!decrease) {
		speed += EngineTime::getDeltaTime();
		if (speed >= 10)
		{
			decrease = true;
		}
	}
	if (decrease) {
		speed -= EngineTime::getDeltaTime();
		if (speed <= 2)
		{
			decrease = false;
		}
	}
	

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);


	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);


	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quads::releaseBuffers()
{
}
