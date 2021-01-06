#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;

	mapSceneList _mSceneList;
	bool _isVideoPlay;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//���߰� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);

	//�� ���� �Լ�
	HRESULT changeScene(string sceneName);

	sceneManager() {};
	~sceneManager() {};
	//���� �� ó���� render ���� �뵵
	void setIsVideoPlay(bool b) { _isVideoPlay = b; };
	bool getIsVideoPlay() { return _isVideoPlay; };
};

