#pragma once
#include "gameNode.h"
#include <map>

class shopScene :public gameNode
{
private:
	//�ⱸ ��Ʈ
	RECT _exit;
	//����̹���
	image* _background;
	image* _img;

	int _selectNum;
	RECT _selectBox;

	////�ߺ�ó�� ���ܵ� ������ ����Ʈ(ItemName, tagItem)
	//map<string, tagItem> _mItem;

	//player ���� ������ itemList
	vector<tagItem> _vItem;
public:
	shopScene();
	~shopScene();
	HRESULT init();
	void release();
	void update();
	void render();
};