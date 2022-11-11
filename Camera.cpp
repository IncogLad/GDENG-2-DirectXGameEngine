#include "Camera.h"
#include "AppWindow.h"
#include "EngineTime.h"
#include "InputSystem.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::initialize(std::string name)
{
	AGameObject::initialize(name);
	InputSystem::get()->addListener(this);
	this->worldCam.setIdentity();
	this->worldCam.setTranslation(Vector3D(0, 20, 0));
	//this->worldCam.setRotationX(90);
	//camPos.zeros();
}

void Camera::destroy()
{
	AGameObject::destroy();
}

void Camera::draw(VertexShader* m_vs, PixelShader* m_ps)
{

}

void Camera::update(float deltaTime)
{
	Matrix4x4 temp; temp.setIdentity();

	temp.setIdentity();

	Matrix4x4 xMatrix; xMatrix.setIdentity();
	xMatrix.setRotationX(1.45);
	temp *= xMatrix;

	Matrix4x4 yMatrix; yMatrix.setIdentity();
	yMatrix.setRotationY(0);
	temp *= yMatrix;


	Vector3D new_pos = worldCam.getTranslation() + temp.getZDirection() * (m_forward * deltaTime * 1.5f);
	new_pos = new_pos + temp.getYDirection() * (m_upward * deltaTime * 1.5f);
	new_pos = new_pos + temp.getXDirection() * (m_rightward * deltaTime * 1.5f);
	temp.setTranslation(new_pos);

	worldCam = temp;

	temp.inverse();
	this->localMatrix = temp;
	
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}


void Camera::onKeyDown(int key)
{
	if (key == 'W')
	{
		this->m_forward = 1.0f;
		std::cout << "W pressed" << std::endl;
		
	}
	else if (key == 'S')
	{
		this->m_forward = -1.0f;
		std::cout << "S pressed" << std::endl;
	}
	else if (key == 'A')
	{
		this->m_rightward = -1.0f;
		std::cout << "A pressed" << std::endl;
	}
	else if (key == 'D')
	{
		this->m_rightward = 1.0f;
		std::cout << "D pressed" << std::endl;
	}
	else if (key == 'Q')
	{
		this->m_upward = 1.0f;
		std::cout << "Q pressed" << std::endl;
	}
	else if (key == 'E')
	{
		this->m_upward = -1.0f;
		std::cout << "E pressed" << std::endl;
	}
}

void Camera::onKeyUp(int key)
{
	this->m_forward = 0.0f;
	this->m_rightward = 0.0f;
	this->m_upward = 0.0f;
}

void Camera::onMouseMove(const Point& mouse_pos)
{

	int width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
	int height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);

	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.5f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.5f;

	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));

}

void Camera::onLeftMouseDown(const Point& mouse_pos)
{

}

void Camera::onLeftMouseUp(const Point& mouse_pos)
{
}

void Camera::onRightMouseDown(const Point& mouse_pos)
{
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
}
