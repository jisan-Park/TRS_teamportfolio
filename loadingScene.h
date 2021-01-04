#pragma once
#include "gameNode.h"

#define LOADINGMAX 1000

class progressBar;

class loadingScene : public gameNode
{
private:
	image* _background;
	image* _loadingCharacter;

public:
	loadingScene();
	~loadingScene();

	//������ ��� ����
	int _currentCount;
	float _currentX;

	HRESULT init();
	void release();
	void update();
	void render();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);
