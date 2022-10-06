#include "Quads.h"


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

void Quads::draw()
{
	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quads::releaseBuffers()
{
}
