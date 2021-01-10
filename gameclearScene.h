#pragma once
#include "gameNode.h"
//���� ����� ���� include
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

class gameclearScene : public gameNode
{
private:
	bool _isStart;
	HWND _introVideo; //���� ����� ���� �ڵ�

	int _videoCount;
public:
	gameclearScene();
	~gameclearScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void KeyManager(); // Ű�Ŵ���
	void VideoPlay(); // ���� ���� �Լ�
	void VideoStop(); // ���� ���� �Լ�
};