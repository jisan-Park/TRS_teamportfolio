#include "stdafx.h"
#include "gameManager.h"

gameManager::gameManager()
{
}

gameManager::~gameManager()
{
}

HRESULT gameManager::init()
{
	renderNum = 0;
	return S_OK;
}

void gameManager::release()
{
}

void gameManager::update()
{
	quicksort(arrPicture, 0, arrPicture.size() - 1);
}

void gameManager::render(HDC hdc)
{
	for (iterPicture = arrPicture.begin(); iterPicture != arrPicture.end(); ++iterPicture) {
		(*iterPicture)->render(hdc);
	}
}
void gameManager::addPicture(characterInfo info, image * img)
{
	picture* temp = new picture;
	temp->init(info, img);
	arrPicture.push_back(temp);
}
void gameManager::addPicture(characterInfo info, image * img, animation * ani)
{
	picture* temp = new picture;
	temp->init(info, img, ani);
	arrPicture.push_back(temp);
}

void gameManager::updatePicture(characterInfo info, image * img, animation * ani)
{
	//�Ϸù�ȣ�� ���� ���� ã�� ������ update
	for (iterPicture = arrPicture.begin(); iterPicture != arrPicture.end(); ++iterPicture) {
		if ((*iterPicture)->getRenderNum() == info.renderNumber) {
			(*iterPicture)->update(info, img, ani);
		}
	}
}

void gameManager::quicksort(vector<picture*>& data, int start, int end)
{
	if (start >= end) {
		//���Ұ� 1���� ���
		return;
	}
	int pivot = start;
	int i = pivot + 1;
	int j = end;
	picture* temp;

	while (i <= j) {
		while (i <= end && data[i]->getInfo().pt_y <= data[pivot]->getInfo().pt_y) {
			i++;
		}
		while (j > start && data[j]->getInfo().pt_y >= data[pivot]->getInfo().pt_y) {
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
	quicksort(data, start, j - 1);
	quicksort(data, j + 1, end);
}

void gameManager::deletePicture(int renderNum)
{
	//�Ϸù�ȣ�� ���� ���� ã�� vector���� erase
	for (iterPicture = arrPicture.begin(); iterPicture != arrPicture.end(); ++iterPicture) {
		if ((*iterPicture)->getRenderNum() == renderNum) {
			iterPicture = arrPicture.erase(iterPicture);
			break;
		}
	}
}