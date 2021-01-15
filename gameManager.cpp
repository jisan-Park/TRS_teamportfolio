#include "stdafx.h"
#include "gameManager.h"
//
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
//
gameManager::gameManager()
{
}

gameManager::~gameManager()
{
}

HRESULT gameManager::init()
{
	
	
	setItem();
	_snackNum = 0;
	_shopNum = 0;
	renderNum = 0;
	_background_volume = 100.0f;
	_SFX_volume = 100.0f;
	setUIimage();
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
	//UI render
	_uiImage->render(hdc, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);

	life_number->frameRender(hdc, CAMERAMANAGER->getCameraPoint().x + 61, CAMERAMANAGER->getCameraPoint().y + 8);

	hp_number_100->frameRender(hdc, CAMERAMANAGER->getCameraPoint().x + 86, CAMERAMANAGER->getCameraPoint().y + 45, (PLAYER->getHp() / 100), 0);
	hp_number_10->frameRender(hdc, CAMERAMANAGER->getCameraPoint().x + 106, CAMERAMANAGER->getCameraPoint().y + 45, (PLAYER->getHp() % 100) / 10, 0);
	hp_number_1->frameRender(hdc, CAMERAMANAGER->getCameraPoint().x + 126, CAMERAMANAGER->getCameraPoint().y + 45, PLAYER->getHp() % 10, 0);

	gp_number_100->frameRender(hdc, CAMERAMANAGER->getCameraPoint().x + 86, CAMERAMANAGER->getCameraPoint().y + 65, PLAYER->getGp() / 100, 0);
	gp_number_10->frameRender(hdc, CAMERAMANAGER->getCameraPoint().x + 106, CAMERAMANAGER->getCameraPoint().y + 65, (PLAYER->getGp() % 100) / 10, 0);
	gp_number_1->frameRender(hdc, CAMERAMANAGER->getCameraPoint().x + 126, CAMERAMANAGER->getCameraPoint().y + 65, PLAYER->getGp() % 10, 0);

	coin_number_100->frameRender(hdc, CAMERAMANAGER->getCameraPoint().x + 86, CAMERAMANAGER->getCameraPoint().y + 85, PLAYER->getMoney() / 100, 0);
	coin_number_10->frameRender(hdc, CAMERAMANAGER->getCameraPoint().x + 106, CAMERAMANAGER->getCameraPoint().y + 85, (PLAYER->getMoney() % 100) / 10, 0);
	coin_number_1->frameRender(hdc, CAMERAMANAGER->getCameraPoint().x + 126, CAMERAMANAGER->getCameraPoint().y + 85, PLAYER->getMoney() % 10, 0);
	if (KEYMANAGER->isOnceKeyDown('P')) {
		cout << "_snackNum = " << _snackNum << endl;
	}
	_snack->render(hdc, CAMERAMANAGER->getCameraPoint().x + 82, CAMERAMANAGER->getCameraPoint().y + 104);
}
void gameManager::setItem()
{
	tagItem temp;

	IMAGEMANAGER->addImage("����ʹ�", "image/shop/����ʹ�.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ʹ�", "image/shop/����ʹ�.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ʹ�", "image/shop/�����ʹ�.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ȸ�ʹ�", "image/shop/��ȸ�ʹ�.bmp", 200, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������ũ", "image/shop/������ũ.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ġŲ", "image/shop/ġŲ.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "image/shop/����.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ܹ���", "image/shop/�ܹ���.bmp", 200, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�Ƹ޸�ī��", "image/shop/�Ƹ޸�ī��.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ī���", "image/shop/ī���.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ǳ����", "image/shop/ǳ����.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ݸ�", "image/shop/���ݸ�.bmp", 200, 100, true, RGB(255, 0, 255));

	temp.img = IMAGEMANAGER->findImage("����ʹ�");
	temp.itemName = "����ʹ�";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("����ʹ�");
	temp.itemName = "����ʹ�";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("�����ʹ�");
	temp.itemName = "�����ʹ�";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("��ȸ�ʹ�");
	temp.itemName = "��ȸ�ʹ�";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("������ũ");
	temp.itemName = "������ũ";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("ġŲ");
	temp.itemName = "ġŲ";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("����");
	temp.itemName = "����";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("�ܹ���");
	temp.itemName = "�ܹ���";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("�Ƹ޸�ī��");
	temp.itemName = "�Ƹ޸�ī��";
	temp.price = 1;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("ī���");
	temp.itemName = "ī���";
	temp.price = 1;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("ǳ����");
	temp.itemName = "ǳ����";
	temp.price = 2;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("���ݸ�");
	temp.itemName = "���ݸ�";
	temp.price = 2;
	_vItem.push_back(temp);
}
void gameManager::setUI()
{//UI
	if (PLAYER->getCharacterNum() == 0) {
		_uiImage = IMAGEMANAGER->findImage("player1");
	}
	else if (PLAYER->getCharacterNum() == 1) {
		_uiImage = IMAGEMANAGER->findImage("player2");
	}
	//_snack;
	if (_snackNum == 0) {
		_snack = IMAGEMANAGER->findImage("none");
	}
	else if (_snackNum == 1) {
		_snack = IMAGEMANAGER->findImage("bubblegum");
	}
	else if (_snackNum == 2) {
		_snack = IMAGEMANAGER->findImage("chocolate");
	}
	//life
	life_number->setFrameX(PLAYER->getLife());
}
void gameManager::setUIimage()
{
	IMAGEMANAGER->addFrameImage("coin_number", "image/UI/coin_number.bmp", 140, 15, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gp_number", "image/UI/gp_number.bmp", 140, 15, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hp_number", "image/UI/hp_number.bmp", 140, 15, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("life_number", "image/UI/life_number.bmp", 112, 30, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("player1", "image/UI/player1.bmp", 150, 130, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player2", "image/UI/player2.bmp", 150, 130, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bubblegum", "image/UI/snack(bubblegum).bmp", 18, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("chocolate", "image/UI/snack(chocolate).bmp", 18, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("none", "image/UI/none.bmp", 18, 19, true, RGB(255, 0, 255));

	_uiImage = new image;
	hp_number_100 = new image;
	hp_number_10 = new image;
	hp_number_1 = new image;
	gp_number_100 = new image;
	gp_number_10 = new image;
	gp_number_1 = new image;
	coin_number_100 = new image;
	coin_number_10 = new image;
	coin_number_1 = new image;
	life_number = new image;
	_snack = new image;

	hp_number_100 = IMAGEMANAGER->findImage("hp_number");
	hp_number_10 = IMAGEMANAGER->findImage("hp_number");
	hp_number_1 = IMAGEMANAGER->findImage("hp_number");

	gp_number_100 = IMAGEMANAGER->findImage("gp_number");
	gp_number_10 = IMAGEMANAGER->findImage("gp_number");
	gp_number_1 = IMAGEMANAGER->findImage("gp_number");

	coin_number_100 = IMAGEMANAGER->findImage("coin_number");
	coin_number_10 = IMAGEMANAGER->findImage("coin_number");
	coin_number_1 = IMAGEMANAGER->findImage("coin_number");

	life_number = IMAGEMANAGER->findImage("life_number");
}
vector<tagItem> gameManager::getItemList(int i)
{
	vector<tagItem> items;
	for (tagItem t : _vItem) {
		if (i == 1) {
			if (t.itemName == "�Ƹ޸�ī��" ||
				t.itemName == "ī���") {
				items.push_back(t);
			}
		}
		else if (i == 2) {
			if (t.itemName == "������ũ" ||
				t.itemName == "����" ||
				t.itemName == "ġŲ" || 
				t.itemName == "�ܹ���") {
				items.push_back(t);
			}
		}
		else if (i == 3) {
			if (t.itemName == "ǳ����" ||
				t.itemName == "���ݸ�") {
				items.push_back(t);
			}
		}
		else if (i == 4) {
			if (t.itemName == "����ʹ�" ||
				t.itemName == "��ȸ�ʹ�" ||
				t.itemName == "�����ʹ�" ||
				t.itemName == "����ʹ�") {
				items.push_back(t);
			}
		}
	}
	return items;
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