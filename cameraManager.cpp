#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	_camera = new camera;
	return S_OK;
}

void cameraManager::release()
{
	if (_camera != nullptr)
	{
		SAFE_DELETE(_camera);
	}
}

void cameraManager::update()
{
	_camera->checkPoint();
	_camera->update();
}

void cameraManager::initCamera(float x, float y)
{
	_camera->init(x, y);
}

void cameraManager::setCamera(float x, float y)
{
	_camera->setCamera(x, y);
}

void cameraManager::moveCamera(float x, float y)
{
	_camera->movePoint(x, y);
}

