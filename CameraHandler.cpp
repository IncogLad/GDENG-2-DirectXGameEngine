#include "CameraHandler.h"
#include "EngineTime.h"

CameraHandler* CameraHandler::sharedInstance = nullptr;

CameraHandler* CameraHandler::getInstance()
{
	return sharedInstance;
}

void CameraHandler::initialize()
{

	sharedInstance = new CameraHandler();
	sharedInstance->sceneCamera = new Camera();
	sharedInstance->sceneCamera->initialize("cam1");
}

void CameraHandler::destroy()
{
	delete sharedInstance;
}

void CameraHandler::update()
{
	
	this->sceneCamera->update(EngineTime::getDeltaTime());
}

Matrix4x4 CameraHandler::getSceneCameraViewMatrix()
{
	return this->sceneCamera->getViewMatrix();

}

Camera* CameraHandler::getSceneCamera()
{
	return this->sceneCamera;
}

CameraHandler::CameraHandler()
{
}

CameraHandler::~CameraHandler()
{
}
