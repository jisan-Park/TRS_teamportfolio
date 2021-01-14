#include "stdafx.h"
#include "shopScene.h"

shopScene::shopScene()
{
}

shopScene::~shopScene()
{
}

HRESULT shopScene::init()
{
	IMAGEMANAGER->addImage("shopscene���", "image/scene/shopscene���.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("shopsceneBox", "image/scene/shopsceneBox.bmp", 200, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ī��", "image/shop/ī��.bmp", 600, 450, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 600, 450, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 600, 450, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 600, 450, true, RGB(255, 0, 255));
	_selectNum = 0;

	_exit = RectMake(CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y + 150, 20, 300);
	//������ ����Ʈ �޾ƿ���
	_vItem = GAMEMANAGER->getItemList(GAMEMANAGER->getShopNum());

	_img = new image;
	if (GAMEMANAGER->getShopNum() == 1) {
		_img = IMAGEMANAGER->findImage("ī��");
	}
	if (GAMEMANAGER->getShopNum() == 2) {
		_img = IMAGEMANAGER->findImage("������");
	}
	if (GAMEMANAGER->getShopNum() == 3) {
		_img = IMAGEMANAGER->findImage("������");
	}
	if (GAMEMANAGER->getShopNum() == 4) {
		_img = IMAGEMANAGER->findImage("������");
	}
	SOUNDMANAGER->stop("������");
	SOUNDMANAGER->stop("�޴�");
	SOUNDMANAGER->stop("�ΰ���");
	SOUNDMANAGER->play("����", 1.0f);


	return S_OK;
}

void shopScene::release()
{
}

void shopScene::update()
{
	RECT temp;
	GAMEMANAGER->setUI();

	if (IntersectRect(&temp, &_exit, &PLAYER->getInfo().chr_rc)) {
		SCENEMANAGER->changeScene("�ΰ��Ӿ�");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
		_selectNum--;
		if (_selectNum < 0) {
			_selectNum = _vItem.size() - 1;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
		_selectNum++;
		if (_selectNum > _vItem.size() - 1) {
			_selectNum = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		//���ݸ�ŭ ����
		if (PLAYER->getMoney() > _vItem[_selectNum].price) {
			PLAYER->setMoney(PLAYER->getMoney() - _vItem[_selectNum].price);
			//���õ� ���������� �÷��̾� �ٲ���
			setPlayer(_vItem[_selectNum].itemName);
		}
		//���ŵǾ��ٴ� ���� �˷��ִ� sound �ʿ�


	}
	PLAYER->update();
	KEYANIMANAGER->update();
}

void shopScene::render()
{
	//�������
	IMAGEMANAGER->findImage("shopscene���")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);
	//���� image
	_img->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);
	//player + UI render
	GAMEMANAGER->render(getMemDC());
	//itemList ���
	for (int i = 0; i < _vItem.size(); ++i) {
		_vItem[i].img->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 600, CAMERAMANAGER->getCameraPoint().y + (i * 100));
	}
	//rect�߰��������
	IMAGEMANAGER->findImage("shopsceneBox")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 600, CAMERAMANAGER->getCameraPoint().y + (_selectNum * 100));
}

void shopScene::setPlayer(string itemKeyName)
{
	if (itemKeyName == "�Ƹ޸�ī��") {
		PLAYER->setHp(PLAYER->getMaxHP());
	}
	if (itemKeyName == "ī���") {
		PLAYER->setGp(PLAYER->getMaxGP());
	}
	if (itemKeyName == "����ʹ�" || itemKeyName == "������ũ") {
		PLAYER->setStr(PLAYER->getStr() + 10);
	}
	if (itemKeyName == "��ȸ�ʹ�" || itemKeyName == "����") {
		PLAYER->setDef(PLAYER->getDef() + 10);
	}
	if (itemKeyName == "�����ʹ�" || itemKeyName == "ġŲ") {
		PLAYER->setSpd(PLAYER->getSpd() + 10);
	}
	if (itemKeyName == "����ʹ�" || itemKeyName == "�ܹ���") {
		PLAYER->setWp(PLAYER->getWp() + 10);
	}
	if (itemKeyName == "ǳ����") {
		GAMEMANAGER->setSnackNum(1);
	}
	if (itemKeyName == "���ݸ�") {
		GAMEMANAGER->setSnackNum(2);
	}
}