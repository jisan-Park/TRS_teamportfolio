#pragma once
#include "gameNode.h"
#include "square.h"
#include <vector>
#include <algorithm>
class playGround : public gameNode
{
private:
	vector<square*> _vSquare;
	vector<square*>::iterator _viSquare;


public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render();	//�׸��� ����

	void quick_sort(vector<square*> &data, int start, int end);
};
