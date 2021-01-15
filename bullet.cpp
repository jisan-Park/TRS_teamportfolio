#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init()
{
	setImage();
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{

	collisionBullet();
}

void bullet::render()
{
}

void bullet::setImage()
{
	IMAGEMANAGER->addFrameImage("devil_bullet", "image/BOSS/devil bullet.bmp", 1200, 304, 8, 2, true, RGB(255, 0, 255));
}

void bullet::collisionBullet()
{

	RECT temp;
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();) {

		_viBullet->_info.physics();
		_viBullet->ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
		GAMEMANAGER->updatePicture(_viBullet->_info, _viBullet->img, _viBullet->ani);

		if (_viBullet->_info.shdDistance < 10) //블렛이의 중점 y좌표가 그림자y좌표보다 커졋을때
		{													//지워줌
			GAMEMANAGER->deletePicture(_viBullet->_info.renderNumber);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else if (IntersectRect(&temp, &PLAYER->getInfo().chr_rc, &_viBullet->_info.chr_rc)) {

			PLAYER->setEnemyAtkRc(_viBullet->_info.chr_rc, 8);
	
			GAMEMANAGER->deletePicture(_viBullet->_info.renderNumber);
			_viBullet = _vBullet.erase(_viBullet);

		}
		else {
			++_viBullet;
		}
	}
}

void bullet::firebullet(float pt_x, float pt_y, float chr_y, float pp)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet._info.init(GAMEMANAGER->getRenderNum(),
		pt_x, pt_y, 50, 50, 50, 50);

	bullet._info.hPushPower = pp;
	bullet._info.jumpPower = -abs(pp);
	bullet._info.gravity = 0;
	bullet._info.pt_y += chr_y;

	bullet.img = new image;
	bullet.img = IMAGEMANAGER->findImage("devil_bullet");
	bullet.ani = new animation;
	bullet.ani->init(IMAGEMANAGER->findImage("devil_bullet")->getWidth(),
		IMAGEMANAGER->findImage("devil_bullet")->getHeight(),
		IMAGEMANAGER->findImage("devil_bullet")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_bullet")->getFrameHeight());
	bullet.ani->setPlayFrame(0, 2, false, true);
	bullet.ani->setFPS(10);
	bullet.ani->start();
	bullet.isFire = false;
	_vBullet.push_back(bullet);
	GAMEMANAGER->addPicture(bullet._info, bullet.img, bullet.ani);

}



