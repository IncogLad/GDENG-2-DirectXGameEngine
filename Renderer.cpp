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

void Renderer::initializeQuads(std::string name, void* shader_byte_code, size_t size_shader)
{
	Quads* tempQuad = new Quads();
	tempQuad->initialize(name);
	tempQuad->initBuffers(shader_byte_code, size_shader);
	insertQuads(tempQuad);
}

void Renderer::initializeQuadsAnim(std::string name, void* shader_byte_code, size_t size_shader)
{
	Quads* tempQuad = new Quads();
	tempQuad->initialize(name);
	tempQuad->initAnimBuffers(shader_byte_code, size_shader);
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

void Renderer::initializeCube(std::string name, void* shader_byte_code, size_t size_shader, int num = 0)
{
	Cube* cube = new Cube();
	cube->initialize(name);
	cube->initBuffers(shader_byte_code, size_shader, num);
	insertCube(cube);
}

void Renderer::initializeCubeConst()
{
	int num = 0;
	/*float p_secondLevel = 0.85f;
	float p_thirdLevel = 2.45f;
	float s_secondLevel = 1.6f;
	float s_thirdLevel = 3.2f;

	float tempx = 0;
	float tempy = 0;
	float tempx2 = 1;
	float tempx3 = 2;

	Vector3D rightSlant = Vector3D(0, 0, 45);
	Vector3D leftSlant = Vector3D(0, 0, -45);*/

	for (auto const& i : sharedInstance->getCubeList()) {
		i->initConstBuffers();
		

		//no7
		/*i->setScale(1, 1, 0.75f);

		Vector3D temp = Vector3D(tempx + num, tempy, 0);
		i->setPosition(temp);

		if (num == 0 || num == 2 || num == 4 || num == 8 || num == 10 || num == 13) 
		{
			i->setRotation(rightSlant);
			if (num == 8)
			{
				Vector3D temp = Vector3D(tempx2 + 0, tempy + s_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 10)
			{
				Vector3D temp = Vector3D(tempx2 + 2, tempy + s_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 13)
			{
				Vector3D temp = Vector3D(tempx3 + 0, tempy + s_thirdLevel, 0);
				i->setPosition(temp);
			}
		}
		if (num == 1 || num == 3 || num == 5 || num == 9 || num == 11 || num == 14)
		{
			i->setRotation(leftSlant);
			if (num == 9)
			{
				Vector3D temp = Vector3D(tempx2 + 1, tempy + s_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 11)
			{
				Vector3D temp = Vector3D(tempx2 + 3, tempy + s_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 14)
			{
				Vector3D temp = Vector3D(tempx3 + 1, tempy + s_thirdLevel, 0);
				i->setPosition(temp);
			}
		}
		if (num == 6 || num == 7 || num == 12)
		{
			i->setRotation(Vector3D::zeros());
			i->setScale(1.5f, 1, 0.75f);

			if (num == 6) {
				Vector3D temp = Vector3D(tempx + 1.5f, tempy + p_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 7)
			{
				Vector3D temp = Vector3D(tempx + 3.5f, tempy + p_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 12)
			{
				Vector3D temp = Vector3D(tempx + 2.5f, tempy + p_thirdLevel, 0);
				i->setPosition(temp);
			}
		}*/

		num++;
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
