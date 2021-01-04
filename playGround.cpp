#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요
HRESULT playGround::init()
{
	gameNode::init(true);
	IMAGEMANAGER->addImage("배경", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	square* temp = new square;
	{
	
	temp->init(WINSIZEX / 2 - 50, WINSIZEY / 2 - 50, 100, 100);
	_vSquare.push_back(temp);
	temp = new square;
	temp->init(WINSIZEX / 2 + 100, WINSIZEY / 2 + 100, 100, 100);
	_vSquare.push_back(temp);
	temp = new square;
	temp->init(WINSIZEX / 2 + 50, WINSIZEY / 2 + 50, 100, 100);
	_vSquare.push_back(temp);
	temp = new square;
	temp->init(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	_vSquare.push_back(temp);
	}
	

	

	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	gameNode::release();

}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();
	//정렬함수  #include <algorithm>-sort 라이브러리함수
	//sort(_vSquare.begin(), _vSquare.end());

	quick_sort(_vSquare, 0, 3);
}

//제발 여기다 그려라 좀...
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	IMAGEMANAGER->findImage("배경")->render(getMemDC());
	for (int i = 0; i < _vSquare.size();i++) {
		_vSquare[i]->render(getMemDC());
	}

	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}
void playGround::quick_sort(vector<square*> &data, int start, int end)
{
	if (start >= end) {
		//원소가 1개인 경우
		return;
	}
	int pivot = start;
	int i = pivot + 1;
	int j = end;
	square* temp;

	while (i <= j) {
		while (i <= end && data[i]->_y <= data[pivot]->_y) {
			i++;
		}
		while (j > start && data[j]->_y >= data[pivot]->_y) {
			j--;
		}
		if (i > j) {
			//엇갈림
			temp = data[j];
			data[j] = data[pivot];
			data[pivot] = temp;
		}
		else {
			//i번째와 j번째를 swap
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}
	quick_sort(data, start, j - 1);
	quick_sort(data, j + 1, end);
}