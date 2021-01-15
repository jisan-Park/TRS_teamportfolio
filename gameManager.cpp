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

	IMAGEMANAGER->addImage("°è¶õÃÊ¹ä", "image/shop/°è¶õÃÊ¹ä.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Àå¾îÃÊ¹ä", "image/shop/Àå¾îÃÊ¹ä.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¿¬¾îÃÊ¹ä", "image/shop/¿¬¾îÃÊ¹ä.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("À°È¸ÃÊ¹ä", "image/shop/À°È¸ÃÊ¹ä.bmp", 200, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("½ºÅ×ÀÌÅ©", "image/shop/½ºÅ×ÀÌÅ©.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ä¡Å²", "image/shop/Ä¡Å².bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÇÇÀÚ", "image/shop/ÇÇÀÚ.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÇÜ¹ö°Å", "image/shop/ÇÜ¹ö°Å.bmp", 200, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("¾Æ¸Þ¸®Ä«³ë", "image/shop/¾Æ¸Þ¸®Ä«³ë.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ä«Æä¶ó¶¼", "image/shop/Ä«Æä¶ó¶¼.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ç³¼±²­", "image/shop/Ç³¼±²­.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÃÊÄÝ¸´", "image/shop/ÃÊÄÝ¸´.bmp", 200, 100, true, RGB(255, 0, 255));

	temp.img = IMAGEMANAGER->findImage("°è¶õÃÊ¹ä");
	temp.itemName = "°è¶õÃÊ¹ä";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("Àå¾îÃÊ¹ä");
	temp.itemName = "Àå¾îÃÊ¹ä";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("¿¬¾îÃÊ¹ä");
	temp.itemName = "¿¬¾îÃÊ¹ä";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("À°È¸ÃÊ¹ä");
	temp.itemName = "À°È¸ÃÊ¹ä";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("½ºÅ×ÀÌÅ©");
	temp.itemName = "½ºÅ×ÀÌÅ©";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("Ä¡Å²");
	temp.itemName = "Ä¡Å²";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("ÇÇÀÚ");
	temp.itemName = "ÇÇÀÚ";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("ÇÜ¹ö°Å");
	temp.itemName = "ÇÜ¹ö°Å";
	temp.price = 3;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("¾Æ¸Þ¸®Ä«³ë");
	temp.itemName = "¾Æ¸Þ¸®Ä«³ë";
	temp.price = 1;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("Ä«Æä¶ó¶¼");
	temp.itemName = "Ä«Æä¶ó¶¼";
	temp.price = 1;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("Ç³¼±²­");
	temp.itemName = "Ç³¼±²­";
	temp.price = 2;
	_vItem.push_back(temp);

	temp.img = IMAGEMANAGER->findImage("ÃÊÄÝ¸´");
	temp.itemName = "ÃÊÄÝ¸´";
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
			if (t.itemName == "¾Æ¸Þ¸®Ä«³ë" ||
				t.itemName == "Ä«Æä¶ó¶¼") {
				items.push_back(t);
			}
		}
		else if (i == 2) {
			if (t.itemName == "½ºÅ×ÀÌÅ©" ||
				t.itemName == "ÇÇÀÚ" ||
				t.itemName == "Ä¡Å²" || 
				t.itemName == "ÇÜ¹ö°Å") {
				items.push_back(t);
			}
		}
		else if (i == 3) {
			if (t.itemName == "Ç³¼±²­" ||
				t.itemName == "ÃÊÄÝ¸´") {
				items.push_back(t);
			}
		}
		else if (i == 4) {
			if (t.itemName == "Àå¾îÃÊ¹ä" ||
				t.itemName == "À°È¸ÃÊ¹ä" ||
				t.itemName == "¿¬¾îÃÊ¹ä" ||
				t.itemName == "°è¶õÃÊ¹ä") {
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
	//ÀÏ·Ã¹øÈ£°¡ °°Àº °ÍÀ» Ã£¾Æ Á¤º¸¸¦ update
	for (iterPicture = arrPicture.begin(); iterPicture != arrPicture.end(); ++iterPicture) {
		if ((*iterPicture)->getRenderNum() == info.renderNumber) {
			(*iterPicture)->update(info, img, ani);
		}
	}
}

void gameManager::quicksort(vector<picture*>& data, int start, int end)
{
	if (start >= end) {
		//¿ø¼Ò°¡ 1°³ÀÎ °æ¿ì
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
			//¾ù°¥¸²
			temp = data[j];
			data[j] = data[pivot];
			data[pivot] = temp;
		}
		else {
			//i¹øÂ°¿Í j¹øÂ°¸¦ swap
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
	//ÀÏ·Ã¹øÈ£°¡ °°Àº °ÍÀ» Ã£¾Æ vector¿¡¼­ erase
	for (iterPicture = arrPicture.begin(); iterPicture != arrPicture.end(); ++iterPicture) {
		if ((*iterPicture)->getRenderNum() == renderNum) {
			iterPicture = arrPicture.erase(iterPicture);
			break;
		}
	}
}