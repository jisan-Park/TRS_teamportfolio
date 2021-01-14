#pragma once
#include "gameNode.h"
#include <map>

class shopScene :public gameNode
{
private:
	//출구 렉트
	RECT _exit;
	//배경이미지
	image* _background;
	image* _img;

	int _selectNum;
	RECT _selectBox;

	////중복처리 제외된 아이템 리스트(ItemName, tagItem)
	//map<string, tagItem> _mItem;

	//player 에게 보여줄 itemList
	vector<tagItem> _vItem;
public:
	shopScene();
	~shopScene();
	HRESULT init();
	void release();
	void update();
	void render();
};