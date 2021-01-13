#pragma once
#include "singletonBase.h"
#include "camera.h"

class cameraManager : public singletonBase <cameraManager>
{
private:
	camera* _camera;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();

	void initCamera(float x, float y);
	void moveCamera(float x, float y);
	//setter
	void setCamera(float x, float y);
	void setCameraStop(bool b) { _camera->setStop(b); };
	void setPhase(int i) { _camera->setPhase(i); };
	//getter
	POINT getCameraPoint() { return _camera->getPoint(); };
	int getCameraPhase() { return _camera->getPhase(); };

};