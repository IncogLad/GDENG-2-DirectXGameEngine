#include "Renderer.h"
#include "AppWindow.h"
#include "SwapChain.h"


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
	quadList.push_front(quad);
}

void Renderer::releaseQuads()
{

}

std::list<Quads*> Renderer::getQuadList()
{
	return quadList;
}

void Renderer::initializeCube(void* shader_byte_code, size_t size_shader, int num = 0)
{
	Cube* cube = new Cube();
	cube->initialize();
	cube->initBuffers(shader_byte_code, size_shader, num);
	insertCube(cube);
}

void Renderer::initializeCubeConst()
{
	for (auto const& i : sharedInstance->getCubeList()) {
		i->initConstBuffers();
	}
}

void Renderer::insertCube(Cube* cube)
{
	cubeList.push_front(cube);
}

void Renderer::releaseCubes()
{
}

std::list<Cube*> Renderer::getCubeList()
{
	return cubeList;
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}
