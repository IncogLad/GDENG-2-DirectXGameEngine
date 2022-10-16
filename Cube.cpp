#include "Cube.h"
#include <random>
#include "AppWindow.h"
#include "Renderer.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "EngineTime.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::initialize()
{
	AGameObject::initialize();
}

void Cube::destroy()
{
	AGameObject::destroy();
}

void Cube::initBuffers( void* shader_byte_code, size_t size_shader, int num = 0)
{
	vertexCube cube_vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(1.f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(1.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,1.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(1.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,1.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,1.2f,1.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,1.2f,0) }

	};

	vertexCube plane_vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(0,0,0),  Vector3D(0,0,0) },
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(0,0,0), Vector3D(0,0,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(0,0,0),  Vector3D(0,0,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),     Vector3D(0,0,0), Vector3D(0,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,0,0), Vector3D(0,0,0) },
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,0,0), Vector3D(0,0,0) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,0,0),  Vector3D(0,0,0) },
		{ Vector3D(-0.5f,0.5f,0.5f),     Vector3D(0,0,0), Vector3D(0,0,0) }

	};

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	if (num == 0) {
		UINT size_list = ARRAYSIZE(cube_vertex_list);
		//std::cout << list->position.m_x << std::endl;
		m_vb->load(cube_vertex_list, sizeof(vertexCube), size_list, shader_byte_code, size_shader);
	}
	else {
		UINT size_list = ARRAYSIZE(plane_vertex_list);
		//std::cout << list->position.m_x << std::endl;
		m_vb->load(plane_vertex_list, sizeof(vertexCube), size_list, shader_byte_code, size_shader);
	}



	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	m_ib = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib->load(index_list, size_index_list);

}

void Cube::initConstBuffers()
{
	cc.m_angle = 0.0f;
	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Cube::draw(VertexShader* m_vs, PixelShader* m_ps)
{
	AGameObject::draw(m_vs, m_ps);
	updateTransforms();


	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);


	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//SET THE INDECES OF THE TRIANGLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);	

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(),0, 0);

}

void Cube::releaseBuffers()
{

}

void Cube::updateTransforms()
{
	Matrix4x4 temp;

	m_delta_scale += EngineTime::getDeltaTime() * 5.55f;
	cc.m_world.setScale(Vector3D(1, 1, 1));
	if (initRot.m_x != 0) {
		temp.setIdentity();
		temp.setRotationZ(initRot.m_x * m_delta_scale);
		cc.m_world *= temp;

		temp.setIdentity();
		temp.setRotationY(initRot.m_y * m_delta_scale);
		cc.m_world *= temp;

		temp.setIdentity();
		temp.setRotationX(initRot.m_z * m_delta_scale);
		cc.m_world *= temp;
	}
	if (initRot.m_x == 0) {
		temp.setIdentity();
		temp.setRotationY(90);
		cc.m_world *= temp;
	}
	if (initRot.m_x == 0) 
		temp.setScale(Vector3D(1, 1, 1));
	else
		temp.setScale(Vector3D(0.25, 0.25, 0.25));
	cc.m_world *= temp;
	if(initRot.m_x == 0)
		temp.setTranslation(initPos);
	else
		temp.setTranslation(initPos + Vector3D(0,0,0.5));

	cc.m_world *= temp;
	

	
	cc.m_view.setIdentity();
	//int width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
	//int height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);
	//cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	
	cc.m_proj.setOrthoLH
	(
		(AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left) / 400.0f,
		(AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);
	

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
}

void Cube::setInitTransforms(Vector3D pos, Vector3D rot)
{
	initPos = pos;
	initRot = rot;
}
