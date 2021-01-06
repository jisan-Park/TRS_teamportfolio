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
	//SCOTT
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_IDLE", "image/player/scott/LEFT_IDLE.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_IDLE", "image/player/scott/RIGHT_IDLE.bmp",2000,250,8,1,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_DASH","image/player/scott/LEFT_DASH.bmp",2000,250,8,1,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_DASH","image/player/scott/RIHGT_DASH.bmp",2000,250,8,1,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_C_YATK","image/player/scott/LEFT_C_YATK.bmp",2250,500,9,2, true, RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_C_YATK", "image/player/scott/RIGHT_C_YATK.bmp",  2250, 500,9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_DASH_GATK", "image/player/scott/LEFT_DASH_GATK.bmp",2000,250,8,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_DASH_GATK", "image/player/scott/RIGHT_DASH_GATK.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_DASH_YATK", "image/player/scott/LEFT_DASH_YATK.bmp",1750,250,7,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_DASH_YATK", "image/player/scott/RIGHT_DASH_YATK.bmp",  1750, 250,7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_DEF", "image/player/scott/LEFT_DEF.bmp",1750,250,7,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_DEF", "image/player/scott/RIGHT_DEF.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_DOWN_ATK", "image/player/scott/LEFT_DOWN_ATK.bmp",1250,250,5,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_DOWN_ATK", "image/player/scott/RIGHT_DOWN_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_G_ATK", "image/player/scott/LEFT_G_ATK.bmp",1750,250,7,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_G_ATK", "image/player/scott/RIGHT_G_ATK.bmp",  1750, 250,7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_G_ATK2", "image/player/scott/LEFT_G_ATK2.bmp",  1750, 250,7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_G_ATK2", "image/player/scott/RIGHT_G_ATK2.bmp",  1750, 250,7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_HITTED", "image/player/scott/LEFT_HITTED.bmp",  1250, 250,5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_HITTED", "image/player/scott/RIGHT_HITTED.bmp",  1250, 250,5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_HITTED2", "image/player/scott/LEFT_HITTED2.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_HITTED2", "image/player/scott/RIGHT_HITTED2.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_HOBJ_ATK", "image/player/scott/LEFT_HOBJ_ATK.bmp",1750,250,7,1,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_HOBJ_ATK", "image/player/scott/RIGHT_HOBJ_ATK.bmp",  1750, 250,7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_HOBJ_GET", "image/player/scott/LEFT_HOBJ_GET.bmp",  500, 250,2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_HOBJ_GET", "image/player/scott/RIGHT_HOBJ_GET.bmp",  500, 250,2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_HOBJ_THROW", "image/player/scott/LEFT_HOBJ_THROW.bmp",1500, 250,  6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_HOBJ_THROW", "image/player/scott/RIGHT_HOBJ_THROW.bmp",  1500, 250,6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_JUMP", "image/player/scott/LEFT_JUMP.bmp", 2250, 500,9, 2,  true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_JUMP", "image/player/scott/RIGHT_JUMP.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_JUMP_GATK", "image/player/scott/LEFT_JUMP_GATK.bmp",  2250, 500,9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_JUMP_GATK", "image/player/scott/RIGHT_JUMP_GATK.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_JUMP_YATK", "image/player/scott/LEFT_JUMP_YATK.bmp",  1750, 250,7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_JUMP_YATK", "image/player/scott/RIGHT_JUMP_YATK.bmp",  1750, 250,7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_ATK","image/player/scott/LEFT_LOBJ_ATK.bmp",1250,250,5,1,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_ATK", "image/player/scott/RIGHT_LOBJ_ATK.bmp",  1250, 250,5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_DASH", "image/player/scott/LEFT_LOBJ_DASH.bmp",2000,250,8,1,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_DASH", "image/player/scott/RIGHT_LOBJ_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_GET", "image/player/scott/LEFT_LOBJ_GET.bmp",  750, 250,3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_GET", "image/player/scott/RIGHT_LOBJ_GET.bmp",  750, 250,3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_IDLE", "image/player/scott/LEFT_LOBJ_IDLE.bmp",  1000, 250,4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_IDLE", "image/player/scott/RIGHT_LOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_JUMP", "image/player/scott/LEFT_LOBJ_JUMP.bmp",  2000, 500,8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_JUMP", "image/player/scott/RIGHT_LOBJ_JUMP.bmp",  2000, 500,8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_JUMPATK", "image/player/scott/LEFT_LOBJ_JUMPATK.bmp",  1250, 250,5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_JUMPATK", "image/player/scott/RIGHT_LOBJ_JUMPATK.bmp",  1250, 250,5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_THROW", "image/player/scott/LEFT_LOBJ_THROW.bmp",  1250, 250,5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_THROW", "image/player/scott/RIGHT_LOBJ_THROW.bmp",  1250, 250,5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_WALK", "image/player/scott/LEFT_LOBJ_WALK.bmp",  1500, 250,6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHTT_LOBJ_WALK", "image/player/scott/RIGHT_LOBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJ_IDLE", "image/player/scott/LEFT_OBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJ_IDLE", "image/player/scott/RIGHT_OBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJ_JUMP", "image/player/scott/LEFT_OBJ_JUMP.bmp",  2250, 500,9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJ_JUMP", "image/player/scott/RIGHT_OBJ_JUMP.bmp",  2250, 500,9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJ_THROW", "image/player/scott/LEFT_OBJ_THROW.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJ_THROW", "image/player/scott/RIGHT_OBJ_THROW.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJ_WALK", "image/player/scott/LEFT_OBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJ_WALK", "image/player/scott/RIGHT_OBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJ_YATK", "image/player/scott/LEFT_OBJ_YATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJ_YATK", "image/player/scott/RIGHT_OBJ_YATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJECT_DASH", "image/player/scott/LEFT_OBJECT_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJECT_DASH", "image/player/scott/RIGHT_OBJECT_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_R_UP", "image/player/scott/LEFT_R_UP.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_R_UP", "image/player/scott/RIGHT_R_UP.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_S_DEF", "image/player/scott/LEFT_S_DEF.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_S_DEF", "image/player/scott/RIGHT_S_DEF.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_SK_ATK", "image/player/scott/LEFT_SK_ATK.bmp", 2250, 750, 9, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_SK_ATK", "image/player/scott/RIGHT_SK_ATK.bmp", 2250, 750, 9, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_STUN", "image/player/scott/LEFT_STUN.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIHGT_STUN", "image/player/scott/RIGHT_STUN.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_THROW", "image/player/scott/LEFT_THROW.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_THROW", "image/player/scott/RIGHT_THROW.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_TIRED", "image/player/scott/LEFT_TIRED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_TIRED", "image/player/scott/RIGHT_TIRED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_UP", "image/player/scott/LEFT_UP.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_UP", "image/player/scott/RIGHT_UP.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_UPPER", "image/player/scott/LEFT_UPPER.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_UPPER", "image/player/scott/RIGHT_UPPER.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_WALK", "image/player/scott/LEFT_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_WALK", "image/player/scott/RIGHT_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_WIN", "image/player/scott/LEFT_WIN.bmp", 2250, 250, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_WIN", "image/player/scott/RIGHT_WIN.bmp", 2250, 250, 9, 2, true, RGB(255, 0, 255));

	//RAMONA
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_IDLE", "image/player/ramona/LEFT_IDLE.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DASH", "image/player/ramona/LEFT_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_C_ATK", "image/player/ramona/LEFT_C_ATK.bmp", 2000, 750, 8, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_C_ATK", "image/player/ramona/RIGHT_C_ATK.bmp", 2000, 750, 8, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT__ATK", "image/player/ramona/LEFT_C_ATK.bmp", 2000, 750, 8, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DASH_YATK", "image/player/ramona/LEFT_DASH_YATK.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_DASH_TATK", "image/player/ramona/RIGHT_DASH_YATK.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DEF", "image/player/ramona/LEFT_DEF.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_DEF", "image/player/ramona/RIGHT_DEF.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DOWN_GATK", "image/player/ramona/LEFT_DOWN_GATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_DOWN_GATK", "image/player/ramona/RIGHT_DOWN_GATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DOWN_YATK", "image/player/ramona/LEFT_DOWN_YATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_DOWN_YATK", "image/player/ramona/RIGHT_DOWN_YATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_G_HITTED", "image/player/ramona/LEFT_G_HITTED.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_G_HITTED", "image/player/ramona/RIGHT_G_HITTED.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_G_HITTED2", "image/player/ramona/LEFT_G_HITTED2.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_G_HITTED2", "image/player/ramona/RIGHT_G_HITTED2.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_GATK", "image/player/ramona/LEFT_GATK.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_GATK", "image/player/ramona/RIGHT_GATK.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_GATK2", "image/player/ramona/LEFT_GATK2.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_GATK2", "image/player/ramona/RIGHT_GATK2.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HITTED", "image/player/ramona/LEFT_HITTED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HITTED", "image/player/ramona/RIGHT_HITTED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_ATK", "image/player/ramona/LEFT_HOBJ_ATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_ATK", "image/player/ramona/RIGHT_HOBJ_ATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_DASH", "image/player/ramona/LEFT_HOBJ_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_DASH", "image/player/ramona/RIGHT_HOBJ_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_GET", "image/player/ramona/LEFT_HOBJ_GET.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_GET", "image/player/ramona/RIGHT_HOBJ_GET.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_IDLE", "image/player/ramona/LEFT_HOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_IDLE", "image/player/ramona/RIGHT_HOBJ_IDLE.bmp",1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_JUMP", "image/player/ramona/LEFT_HOBJ_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_JUMP", "image/player/ramona/RIGHT_HOBJ_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_JUMP_ATK", "image/player/ramona/LEFT_HOBJ_JUMP_ATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_JUMP_ATK", "image/player/ramona/RIGHT_HOBJ_JUMP_ATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_JUMP_THROW", "image/player/ramona/LEFT_HOBJ_JUMP_THROW.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_JUMP_THROW", "image/player/ramona/RIGHT_HOBJ_JUMP_THROW.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_THROW", "image/player/ramona/LEFT_HOBJ_JUMP_THROW.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_THROW", "image/player/ramona/RIGHT_HOBJ_JUMP_THROW.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_WALK", "image/player/ramona/LEFT_HOBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_WALK", "image/player/ramona/RIGHT_HOBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_JUMP", "image/player/ramona/LEFT_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_JUMP", "image/player/ramona/RIGHT_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_JUMP_GATK", "image/player/ramona/LEFT_JUMP_GATK.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_JUMP_GATK", "image/player/ramona/RIGHT_JUMP_GATK.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_JUMP_YATK", "image/player/ramona/LEFT_JUMP_YATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_JUMP_YATK", "image/player/ramona/RIGHT_JUMP_YATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_ATK", "image/player/ramona/LEFT_LOBJ_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_ATK", "image/player/ramona/RIGHT_LOBJ_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_DASH", "image/player/ramona/LEFT_LOBJ_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_DASH", "image/player/ramona/RIGHT_LOBJ_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_GET", "image/player/ramona/LEFT_LOBJ_GET.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_GET", "image/player/ramona/RIGHT_LOBJ_GET.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_IDLE", "image/player/ramona/LEFT_LOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_IDLE", "image/player/ramona/RIGHT_LOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_JUMP", "image/player/ramona/LEFT_LOBJ_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_JUMP", "image/player/ramona/RIGHT_LOBJ_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_JUMP_ATK", "image/player/ramona/LEFT_LOBJ_JUMP_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_JUMP_ATK", "image/player/ramona/RIGHT_LOBJ_JUMP_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_JUMP_THROW", "image/player/ramona/LEFT_LOBJ_JUMP_THROW.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_JUMP_THROW", "image/player/ramona/RIGHT_LOBJ_JUMP_THROW.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_THROW", "image/player/ramona/LEFT_LOBJ_THROW.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_THROW", "image/player/ramona/RIGHT_LOBJ_THROW.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_SK_ATK", "image/player/ramona/LEFT_SK_ATK.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_SK_ATK", "image/player/ramona/RIGHT_SK_ATK.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_SK_ATK2", "image/player/ramona/LEFT_SK_ATK2.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_SK_ATK2", "image/player/ramona/RIGHT_SK_ATK2.bmp", 2000,1000, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_STUN", "image/player/ramona/LEFT_STUN.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_STUN", "image/player/ramona/RIGHT_STUN.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_TIRED", "image/player/ramona/LEFT_TIRED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_TIRED", "image/player/ramona/RIGHT_TIRED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_UP", "image/player/ramona/LEFT_UP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_UP", "image/player/ramona/RIGHT_UP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_WALK", "image/player/ramona/LEFT_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_WALK", "image/player/ramona/RIGHT_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_WIN", "image/player/ramona/LEFT_WIN.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_WIN", "image/player/ramona/RIGHT_WIN.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_YATK", "image/player/ramona/LEFT_YATK.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_YATK", "image/player/ramona/RIGHT_YATK.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
}
