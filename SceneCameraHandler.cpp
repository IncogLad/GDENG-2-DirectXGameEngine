#include "SceneCameraHandler.h"
#include "EngineTime.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = nullptr;

SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return sharedInstance;
}

void SceneCameraHandler::initialize()
{

	sharedInstance = new SceneCameraHandler();
	sharedInstance->sceneCamera = new Camera();
	sharedInstance->sceneCamera->initialize("cam1");
}

void SceneCameraHandler::destroy()
{
	delete sharedInstance;
}

void SceneCameraHandler::update()
{
	
	this->sceneCamera->update(EngineTime::getDeltaTime());
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
	return this->sceneCamera->getViewMatrix();

}

Camera* SceneCameraHandler::getSceneCamera()
{
	return this->sceneCamera;
}

SceneCameraHandler::SceneCameraHandler()
{
}

SceneCameraHandler::~SceneCameraHandler()
{
}
