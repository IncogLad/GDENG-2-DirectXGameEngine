#include "Camera.h"
#include "AppWindow.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::initialize()
{
	AGameObject::initialize();
	m_world_cam.setTranslation(Vector3D(0, 0, -2));
}

void Camera::destroy()
{
	AGameObject::destroy();
}

void Camera::draw(VertexShader* m_vs, PixelShader* m_ps)
{

}

void Camera::update(ConstantBuffer* m_cb)
{
	Matrix4x4 temp;
	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(AppWindow::getInstance()->m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(AppWindow::getInstance()->m_rot_y);
	world_cam *= temp;


	Vector3D new_pos = AppWindow::getInstance()->m_world_cam.getTranslation() + world_cam.getZDirection() * (AppWindow::getInstance()->m_forward * 0.1f);

	new_pos = new_pos + world_cam.getXDirection() * (AppWindow::getInstance()->m_rightward * 0.1f);

	world_cam.setTranslation(new_pos);

	AppWindow::getInstance()->m_world_cam = world_cam;

	world_cam.inverse();

	cc.m_view = world_cam;
	/*cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/300.0f,
		-4.0f,
		4.0f
	);*/

	int width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
	int height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);


	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);


	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
}

void Camera::updatePosition()
{

}
