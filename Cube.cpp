#include "Cube.h"

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
		{Vector3D(-0.25f,-0.25f,-0.25f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.25f,0.25f,-0.25f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.25f,0.25f,-0.25f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.25f,-0.25f,-0.25f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.25f,-0.25f,0.25f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.25f,0.25f,0.25f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.25f,0.25f,0.25f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.25f,-0.25f,0.25f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

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
		m_vb->load(vertex_list, sizeof(vertexCube), size_list, shader_byte_code, size_shader);
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
	//WORLD MATRIX
	cc.m_world.setIdentity();
	Matrix4x4 allMatrix; allMatrix.setIdentity();

	Vector3D moveX = Vector3D(AppWindow::getInstance()->move_cube, 0, 0);
	this->setPosition(moveX);
	
	Matrix4x4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = getLocalRotation();

	Matrix4x4 w_zMatrix; w_zMatrix.setIdentity();
	w_zMatrix.setRotationZ(rotation.m_z);
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

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
	
}
