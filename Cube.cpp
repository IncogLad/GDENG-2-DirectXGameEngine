#include "Cube.h"

#include <random>

#include "AppWindow.h"
#include "Renderer.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "EngineTime.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "SceneCameraHandler.h"


Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::initialize(std::string name)
{
	AGameObject::initialize(name);

	////no.4
	//std::random_device rd; // obtain a random number from hardware
	//std::mt19937 gen(rd()); // seed the generator
	//std::uniform_real_distribution<> distr(-5.f, 5.f);
	//float numx = distr(gen);
	//float numy = distr(gen);
	//float numz = distr(gen);
	//this->setPosition(Vector3D(numx,numy,0));
	//float unumx = distr(gen);
	//float unumy = distr(gen);
	//float unumz = distr(gen);
	rotation = getLocalRotation();
	translation = getLocalPosition();
	scaling = getLocalScale();
	i_scale = false;
	i_trans = false;
}

void Cube::destroy()
{
	AGameObject::destroy();
}

void Cube::initBuffers(void* shader_byte_code, size_t size_shader, int num = 0)
{
	this->num = num;
	vertexCube vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.25f,-0.25f,-0.25f),    Vector3D(1,0,1),  Vector3D(0.2f,0,1) },
		{Vector3D(-0.25f,0.25f,-0.25f),    Vector3D(1,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.25f,0.25f,-0.25f),   Vector3D(1,1,0),  Vector3D(0.2f,1,0) },
		{ Vector3D(0.25f,-0.25f,-0.25f),     Vector3D(0,0,1), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.25f,-0.25f,0.25f),    Vector3D(1,0,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.25f,0.25f,0.25f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.25f,0.25f,0.25f),   Vector3D(0,0,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.25f,-0.25f,0.25f),     Vector3D(0,1,0), Vector3D(1,0,0) }

	};

	vertexCube vertex_list_white_cube[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-1.0f,-1.0f,-1.0f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{Vector3D(-1.0f,1.0f,-1.0f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(1.0f,1.0f,-1.0f),   Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(1.0f,-1.0f,-1.0f),     Vector3D(1,1,1),  Vector3D(1,1,1) },

		//BACK FACE
		{ Vector3D(1.0f,-1.0f,1.0f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(1.0f,1.0f,1.0f),    Vector3D(1,1,1),  Vector3D(1,1,1)},
		{ Vector3D(-1.0f,1.0f,1.0f),   Vector3D(1,1,1),  Vector3D(1,1,1)},
		{ Vector3D(-1.0f,-1.0f,1.0f),     Vector3D(1,1,1),  Vector3D(1,1,1)}

	};

	vertexCube plane_vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-1.0f,0.0f,-1.0f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{Vector3D(-1.0f,0.0f,-1.0f),    Vector3D(1,1,1), Vector3D(1,1,1) },
		{ Vector3D(1.0f,.0f,-1.0f),   Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(1.0f,0.0f,-1.0f),     Vector3D(1,1,1), Vector3D(1,1,1) },

		//BACK FACE
		{ Vector3D(1.0f,0.0f,1.0f),    Vector3D(1,1,1), Vector3D(1,1,1) },
		{ Vector3D(1.0f,0.0f,1.0f),    Vector3D(1,1,1), Vector3D(1,1,1) },
		{ Vector3D(-1.0f,0.0f,1.0f),   Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(-1.0f,0.0f,1.0f),     Vector3D(1,1,1), Vector3D(1,1,1) }

	};

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	if (this->num == 0) {
		UINT size_list = ARRAYSIZE(vertex_list);
		//std::cout << list->position.m_x << std::endl;
		m_vb->load(vertex_list_white_cube, sizeof(vertexCube), size_list, shader_byte_code, size_shader);
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
	updatePosition();


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

void Cube::updatePosition()
{
	float speed = 1.5f / 5;

	//WORLD MATRIX
	cc.m_world.setIdentity();
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	/*
	if (!i_trans) {
		translation.m_x += speed * (float)EngineTime::getDeltaTime();
		if (translation.m_x >= 1)
		{
			i_trans = true;
		}
	}
	else
	{
		translation.m_x -= speed * (float)EngineTime::getDeltaTime();
		if (translation.m_x <= -1)
		{
			i_trans = false;
		}
	}
	*/

	//no6
	if (name == "plane") {
		setScale(Vector3D(4, 4, 4));
	}
	if (name == "cube0")
	{
		setScale(Vector3D(0.5, 0.5, 0.5));
		setPosition(Vector3D(0.0f, 0.9f, 0.0f));
	}
	if (name == "cube1")
	{
		setScale(Vector3D(0.5, 0.5, 0.5));
		setPosition(Vector3D(-1.5f, 2.0f, 0));
	}
	if (name == "cube2")
	{
		setScale(Vector3D(0.5, 0.5, 0.5));
		setPosition(Vector3D(-1.5f, 3.0f, -2.0f));
	}

	
	//
	////no5
	//if (!i_scale) {
	//	if (scaling.m_z < 2.0f)
	//		scaling.m_x += (speed * (float)EngineTime::getDeltaTime());
	//	
	//	if (scaling.m_z < 2.0f)
	//		scaling.m_z += (speed * (float)EngineTime::getDeltaTime());

	//	scaling.m_y -= (speed * (float)EngineTime::getDeltaTime());
	//	if (scaling.m_y <= 0.0f && scaling.m_z >= 2.0f && scaling.m_x >= 2.0f)
	//	{
	//		i_scale = true;
	//	}
	//}
	//else
	//{
	//	if (scaling.m_x > 1.0f)
	//		scaling.m_x -= (speed * (float)EngineTime::getDeltaTime());

	//	if (scaling.m_z > 1.0f)
	//		scaling.m_z -= (speed * (float)EngineTime::getDeltaTime());

	//	scaling.m_y += (speed * (float)EngineTime::getDeltaTime());


	//	if (scaling.m_y >= 1.0f && scaling.m_x <= 1.0f && scaling.m_z <= 1.0f)
	//	{
	//		i_scale = false;
	//	}
	//}

	
	
	//Vector3D translate1 = Vector3D(translation.m_x, translation.m_x, 0);
	//Vector3D moveX = Vector3D(AppWindow::getInstance()->move_cube, 0, 0);
	//this->setPosition(translation);

	//Vector3D scale1 = Vector3D(scaling.m_x, scaling.m_y, scaling.m_z);
	//this->setScale(scale1);
	
	Matrix4x4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->getLocalScale());

	
	/*if (rotation.m_x < 360) {
		rotation.m_x += speed * (float)EngineTime::getDeltaTime();
	}
	else
	{
		rotation.m_x = 0;
	}

	if (rotation.m_y < 360) {
		rotation.m_y += speed * (float)EngineTime::getDeltaTime();
	}
	else
	{
		rotation.m_y = 0;
	}

	if (rotation.m_z < 360) {
		rotation.m_z += speed * (float)EngineTime::getDeltaTime();
	}
	else
	{
		rotation.m_z = 0;
	}*/
	//std::cout << localRotation.m_z << std::endl;

	Matrix4x4 w_zMatrix; w_zMatrix.setIdentity();
	w_zMatrix.setRotationZ(getLocalRotation().m_z);
	allMatrix *= w_zMatrix;

	Matrix4x4 w_xMatrix; w_xMatrix.setIdentity();
	w_xMatrix.setRotationX(rotation.m_x);
	allMatrix *= w_xMatrix;

	Matrix4x4 w_yMatrix; w_yMatrix.setIdentity();
	w_yMatrix.setRotationY(rotation.m_y);
	allMatrix *= w_yMatrix;

	//scaleMatrix *= rotMatrix;
	allMatrix *= scaleMatrix;
	allMatrix *= translationMatrix;
	cc.m_world = allMatrix;

	//VIEW MATRIX
	cc.m_view.setIdentity();
	cc.m_view = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	
	//PROJ MATRIX
	int width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
	int height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);

	//cc.m_proj.setOrthoLH(1.57f, ((float)width / (float)height), 0.1f, 1000.0f);
	cc.m_proj.setPerspectiveFovLH(1.57, ((float)width / (float)height), 0.1f, 1000.0f);

	//std::cout << getLocalPosition().m_x << ", " << getLocalPosition().m_y << ", " << getLocalPosition().m_z << std::endl;

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
	
}
