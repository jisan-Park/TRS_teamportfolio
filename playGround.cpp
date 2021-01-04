#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ���
HRESULT playGround::init()
{
	gameNode::init(true);
	IMAGEMANAGER->addImage("���", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

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

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	gameNode::release();

}

//����(���)�� ����� �ϼ���
void playGround::update()
{
	gameNode::update();
	//�����Լ�  #include <algorithm>-sort ���̺귯���Լ�
	//sort(_vSquare.begin(), _vSquare.end());

	quick_sort(_vSquare, 0, 3);
}

//���� ����� �׷��� ��...
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	IMAGEMANAGER->findImage("���")->render(getMemDC());
	for (int i = 0; i < _vSquare.size();i++) {
		_vSquare[i]->render(getMemDC());
	}

	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}
void playGround::quick_sort(vector<square*> &data, int start, int end)
{
	if (start >= end) {
		//���Ұ� 1���� ���
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
			//������
			temp = data[j];
			data[j] = data[pivot];
			data[pivot] = temp;
		}
		else {
			//i��°�� j��°�� swap
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}
	quick_sort(data, start, j - 1);
	quick_sort(data, j + 1, end);
}