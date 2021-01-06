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

	//씬추가 함수
	gameNode* addScene(string sceneName, gameNode* scene);

	//씬 변경 함수
	HRESULT changeScene(string sceneName);

	sceneManager() {};
	~sceneManager() {};
	//영상 씬 처리시 render 막는 용도
	void setIsVideoPlay(bool b) { _isVideoPlay = b; };
	bool getIsVideoPlay() { return _isVideoPlay; };
};

