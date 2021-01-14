#include "stdafx.h"
#include "Coin.h"

HRESULT Coin::init()
{
	setImage();
	return S_OK;
}

void Coin::release()
{
}

void Coin::update()
{
	for (tagCoin t : _vCoin) {

		t.ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
		GAMEMANAGER->updatePicture(t._info, t.img, t.ani);
	}
	
	collisionCoin();
}

void Coin::render()
{
	
}

void Coin::setImage()
{
	IMAGEMANAGER->addFrameImage("sCoin", "image/coin/smallCoin.bmp", 300, 50., 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mCoin", "image/coin/mediumCoin.bmp", 360, 60, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lCoin", "image/coin/LargeCoin.bmp", 384, 64, 6, 1, true, RGB(255, 0, 255));
}

void Coin::collisionCoin()
{
	RECT temp;
	for (_viCoin = _vCoin.begin(); _viCoin != _vCoin.end();) {
		if (IntersectRect(&temp,&PLAYER->getInfo().chr_rc,&_viCoin->_info.chr_rc)) {
			PLAYER->setMoney(PLAYER->getMoney() + _viCoin->value);
			GAMEMANAGER->deletePicture(_viCoin->_info.renderNumber);
			_viCoin = _vCoin.erase(_viCoin);
		}
		else {
			++_viCoin;
		}
	}
}


void Coin::makeCoin(int num,float x,float y)
{
	//i를 20으로 나눈 값 + 나머지에서 5로 나눈 값 + 나머지에서 1로 나눈 값
	int largeCount = num / 20;
	num = num % 20;
	int middleCount = num /5;
	num = num % 5;
	int smallCount  = num;

	for (int i = 0; i < largeCount;i++) {
		tagCoin t;
		t._info.init(GAMEMANAGER->getRenderNum(),
			x + RND->getFromFloatTo(-20,20),
			y + RND->getFromFloatTo(-20, 20),
			64,64,0,0);
		//t._info.jumpPower = 2;
		t.img = new image;
		t.img = IMAGEMANAGER->findImage("lCoin");
		t.ani = new animation;
		t.ani->init(IMAGEMANAGER->findImage("lCoin")->getWidth(),
			IMAGEMANAGER->findImage("lCoin")->getHeight(),
			IMAGEMANAGER->findImage("lCoin")->getFrameWidth(),
			IMAGEMANAGER->findImage("lCoin")->getFrameHeight());
		t.ani->setPlayFrame(0,5,false,true);
		t.ani->setFPS(12);
		t.ani->start();
		t.value = 20;
		_vCoin.push_back(t);
		GAMEMANAGER->addPicture(t._info,t.img,t.ani);
	}
	for (int i = 0; i < middleCount; i++) {
		tagCoin t;
		t._info.init(GAMEMANAGER->getRenderNum(),
			x + RND->getFromFloatTo(-20, 20),
			y + RND->getFromFloatTo(-20, 20),
			60, 60, 0, 0);
		//t._info.jumpPower = 2;
		t.img = new image;
		t.img = IMAGEMANAGER->findImage("mCoin");
		t.ani = new animation;
		t.ani->init(IMAGEMANAGER->findImage("mCoin")->getWidth(),
			IMAGEMANAGER->findImage("mCoin")->getHeight(),
			IMAGEMANAGER->findImage("mCoin")->getFrameWidth(),
			IMAGEMANAGER->findImage("mCoin")->getFrameHeight());
		t.ani->setPlayFrame(0, 5, false, true);
		t.ani->setFPS(12);
		t.ani->start();
		t.value = 5;
		_vCoin.push_back(t);
		GAMEMANAGER->addPicture(t._info, t.img, t.ani);
	}
	for (int i = 0; i < smallCount; i++) {
		tagCoin t;
		t._info.init(GAMEMANAGER->getRenderNum(),
			x + RND->getFromFloatTo(-20, 20),
			y + RND->getFromFloatTo(-20, 20),
			50, 50, 0, 0);
		//t._info.jumpPower = 2;
		t.img = new image;
		t.img = IMAGEMANAGER->findImage("sCoin");
		t.ani = new animation;
		t.ani->init(IMAGEMANAGER->findImage("sCoin")->getWidth(),
			IMAGEMANAGER->findImage("sCoin")->getHeight(),
			IMAGEMANAGER->findImage("sCoin")->getFrameWidth(),
			IMAGEMANAGER->findImage("sCoin")->getFrameHeight());
		t.ani->setPlayFrame(0, 5, false, true);
		t.ani->setFPS(12);
		t.ani->start();
		t.value = 1;
		_vCoin.push_back(t);
		GAMEMANAGER->addPicture(t._info, t.img, t.ani);
	}
}

