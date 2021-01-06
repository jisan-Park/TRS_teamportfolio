#pragma once
#include "gameNode.h"
struct tagItem {
	string name;

};
class shopScene:public gameNode
{
private:
	image* _img;

	vector<tagItem> _vItem;
public:
	shopScene();
	~shopScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

