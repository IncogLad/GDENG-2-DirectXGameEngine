#pragma once
#include <list>

#include "Quads.h"
#include "Cube.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	static Renderer* getInstance();
	static void initialize();
	static void destroy();

	void initializeQuads(std::string name, struct vertex list[], void* shader_byte_code, size_t size_shader);
	void initializeQuadsAnim(std::string name, struct vertexAnim list[], void* shader_byte_code, size_t size_shader);
	void initializeQuadConst();
	void insertQuads(class Quads* quad);
	void releaseQuads();
	std::list<class Quads*> getQuadList();

	void initializeCube(std::string name, void* shader_byte_code, size_t size_shader, int num );
	void initializeCubeConst();
	void insertCube(class Cube* cube);
	void releaseCubes();
	std::list<class Cube*> getCubeList();

	
private:
	static Renderer* sharedInstance;
	std::list<class Quads*> quadList;
	std::list<class Cube*> cubeList;

	Renderer(Renderer const&) {};
	Renderer& operator=(Renderer const&) {};
	

};

