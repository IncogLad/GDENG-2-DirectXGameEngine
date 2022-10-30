#pragma once
#include "Camera.h"

class SceneCameraHandler
{

public:
	static SceneCameraHandler* getInstance();
	static void initialize();
	static void destroy();

	void update();

	Matrix4x4 getSceneCameraViewMatrix();
	Camera* getSceneCamera();

private:
	SceneCameraHandler();
	~SceneCameraHandler();

	static SceneCameraHandler* sharedInstance;

	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};

	Camera* sceneCamera;

};

