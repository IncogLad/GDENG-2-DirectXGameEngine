#include "Renderer.h"

Renderer* Renderer::sharedInstance = nullptr;

Renderer* Renderer::getInstance()
{
    return sharedInstance;
}   

void Renderer::initialize()
{
    sharedInstance = new Renderer();
}

void Renderer::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->releaseQuads();
	}
    
}

void Renderer::initializeQuads(vertex list[], void* shader_byte_code, size_t size_shader)
{
	Quads* tempQuad = new Quads();
	tempQuad->initialize();
	tempQuad->initBuffers(list, shader_byte_code, size_shader);
	insertQuads(tempQuad);
}

void Renderer::initializeQuadsAnim(vertexAnim list[], void* shader_byte_code, size_t size_shader)
{
	Quads* tempQuad = new Quads();
	tempQuad->initialize();
	tempQuad->initAnimBuffers(list, shader_byte_code, size_shader);
	insertQuads(tempQuad);
}

void Renderer::initializeQuadConst()
{
	for (auto const& i : sharedInstance->getQuadList()) {
		i->initConstBuffers();
	}
}

void Renderer::insertQuads(Quads* quad)
{
	vertexBufferList.push_front(quad);
}

void Renderer::releaseQuads()
{

}

std::list<Quads*> Renderer::getQuadList()
{
	
	return vertexBufferList;
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}
