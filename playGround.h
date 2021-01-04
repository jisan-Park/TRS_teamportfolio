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

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render();	//그리기 전용

	void quick_sort(vector<square*> &data, int start, int end);
};
