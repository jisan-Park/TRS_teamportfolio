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
	void setCamera(float x, float y);
	void moveCamera(float x, float y);
	POINT getCameraPoint();
};