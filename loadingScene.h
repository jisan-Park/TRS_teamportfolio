#pragma once
#include "gameNode.h"

#define LOADINGMAX 500

class progressBar;

class loadingScene : public gameNode
{
private:
	image* _background;
	image* _loadingCharacter;

public:
	loadingScene();
	~loadingScene();

	//스레드 사용 변수
	int _currentCount;
	float _currentX;

	HRESULT init();
	void release();
	void update();
	void render();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);
