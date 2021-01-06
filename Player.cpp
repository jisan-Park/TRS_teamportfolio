#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::init()
{
	setImage();
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
}

void Player::render()
{
}

void Player::setImage()
{
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_IDLE", "image/player/scott/LEFT_IDLE.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_DASH","image/player/scott/LEFT_DASH.bmp",2000,250,8,1,true,RGB(255,0,255));
	
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_IDLE", "image/player/ramona/LEFT_IDLE.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DASH", "image/player/ramona/LEFT_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
}
