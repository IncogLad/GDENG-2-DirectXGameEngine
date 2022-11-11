#pragma once
#include "Camera.h"
#include <list>
#include <unordered_map>

typedef std::string String;
typedef std::list<Camera*> CameraList;
typedef std::unordered_map<String, Camera*> CameraTable;

class CameraHandler
{

public:
	static CameraHandler* getInstance();
	static void initialize();
	static void destroy();

	void update();

	Matrix4x4 getSceneCameraViewMatrix();
	Camera* getSceneCamera();

private:
	CameraHandler();
	~CameraHandler();

	static CameraHandler* sharedInstance;

	CameraHandler(CameraHandler const&) {};
	CameraHandler& operator=(CameraHandler const&) {};

	Camera* sceneCamera;
	CameraList camera_list_;
	CameraTable camera_table_;


};

