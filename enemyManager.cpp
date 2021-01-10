#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init()
{
	setimage();
	setEnemy();
	
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); _viMinion++)
	{
		(*_viMinion)->update();

	}
}

void enemyManager::render()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); _viMinion++)
	{
		(*_viMinion)->render();
	}
}

void enemyManager::setEnemy()
{
	enemy* temp;
	temp = new mike;
	temp->init("mike_idle", 400, 300);
	_vMinion.push_back(temp);

	temp = new lee;
	temp->init("lee_idle", 600, 300);
	_vMinion.push_back(temp);

	temp = new jesse;
	temp->init("jesse_idle", 300, 300);
	_vMinion.push_back(temp);

	temp = new william;
	temp->init("william_idle", 300, 500);
	_vMinion.push_back(temp);
}

void enemyManager::setimage()
{
	//mike
	IMAGEMANAGER->addFrameImage("mike_idle", "image/enemy/mike/idle.bmp", 600, 300, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mike_attack", "image/enemy/mike/attack(punch).bmp", 1200, 300, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mike_walk", "image/enemy/mike/walk.bmp", 900, 300, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mike_damage", "image/enemy/mike/damage.bmp", 450, 300, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mike_damageDown", "image/enemy/mike/damageDown.bmp", 450, 300, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mike_knockDown", "image/enemy/mike/knockDown.bmp", 2100, 300, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mike_knockUp", "image/enemy/mike/knockUp.bmp", 1200, 300, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mike_held", "image/enemy/mike/held.bmp", 450, 300, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mike_held_lightAttack", "image/enemy/mike/held(light_attack).bmp", 450, 300, 3, 2, true, RGB(255, 0, 255));

	//lee
	IMAGEMANAGER->addFrameImage("lee_idle", "image/enemy/lee/idle.bmp", 600, 300, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lee_attack", "image/enemy/lee/attack(kick).bmp", 900, 300, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lee_walk", "image/enemy/lee/walk.bmp", 900, 300, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lee_damage", "image/enemy/lee/damage.bmp", 450, 300, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lee_damageDown", "image/enemy/lee/damageDown.bmp", 450, 300, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lee_pressDown", "image/enemy/lee/pressDown.bmp", 300, 300, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lee_knockDown", "image/enemy/lee/knockDown.bmp", 2100, 300, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lee_knockUp", "image/enemy/lee/knockUp.bmp", 1200, 300, 8, 2, true, RGB(255, 0, 255));

	//jesse
	IMAGEMANAGER->addFrameImage("jesse_idle", "image/enemy/jesse/idle.bmp", 600, 300, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jesse_attack1", "image/enemy/jesse/attack(uppercut).bmp", 1200, 300, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jesse_attack2", "image/enemy/jesse/attack(jumpkick).bmp", 750, 300, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jesse_walk", "image/enemy/jesse/walk.bmp", 900, 300, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jesse_damage", "image/enemy/jesse/damage.bmp", 450, 300, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jesse_damageDown", "image/enemy/jesse/damageDown.bmp", 450, 300, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jesse_knockDown", "image/enemy/jesse/knockDown.bmp", 2100, 300, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jesse_knockUp", "image/enemy/jesse/knockUp.bmp", 1200, 300, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jesse_jump", "image/enemy/jesse/jump.bmp", 1950, 340, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jesse_run", "image/enemy/jesse/run.bmp", 1200, 300, 8, 2, true, RGB(255, 0, 255));

	//william
	IMAGEMANAGER->addFrameImage("william_idle", "image/enemy/william/idle.bmp", 800, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("william_attack", "image/enemy/william/attack(belly).bmp", 1400, 400, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("william_walk", "image/enemy/william/walk.bmp", 1600, 400, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("william_damage", "image/enemy/william/damage.bmp", 800, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("william_damageDown", "image/enemy/william/damageDown.bmp", 600, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("william_knockDown", "image/enemy/william/knockDown.bmp", 2800, 400, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("william_knockUp", "image/enemy/willaim/knockUp.bmp", 2200, 400, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("william_defence", "image/enemy/willaim/defence.bmp", 1400, 400, 7, 2, true, RGB(255, 0, 255));

	//richard
	IMAGEMANAGER->addFrameImage("richard_idle", "image/enemy/richard/idle.bmp", 1000, 500, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_run", "image/enemy/richard/run.bmp", 1500, 500, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_damage", "image/enemy/richard/damage.bmp", 750, 500, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_damageDown", "image/enemy/richard/damageDown.bmp", 450, 300, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_knockDown", "image/enemy/richard/knockDown.bmp", 3500, 500, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_knockUp", "image/enemy/richard/knockUp.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_hobj_attack", "image/enemy/richard/hobj_attack(throw).bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_hobj_idle", "image/enemy/richard/hobj_idle.bmp", 1000, 500, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_hobj_pick", "image/enemy/richard/hobj_pick.bmp", 500, 500, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_hobj_run", "image/enemy/richard/hobj_run.bmp", 1500, 500, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_lobj_attack", "image/enemy/richard/lobj_attack(throw).bmp", 1250, 500, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_lobj_idle", "image/enemy/richard/lobj_idle.bmp", 1000, 500, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_lobj_pick", "image/enemy/richard/lobj_pick.bmp", 750, 500, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("richard_lobj_run", "image/enemy/richard/lobj_run.bmp", 1500, 500, 6, 2, true, RGB(255, 0, 255));

	//luke
	IMAGEMANAGER->addFrameImage("luke_idle", "image/enemy/luke/idle.bmp", 600, 300, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("luke_attack1", "image/enemy/luke/attack(punch).bmp", 1200, 300, 8, 2, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addFrameImage("luke_attack2", "image/enemy/luke/attack(roundkick).bmp", 1050, 300, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("luke_walk", "image/enemy/luke/walk.bmp", 900, 300, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("luke_damage", "image/enemy/luke/damage.bmp", 450, 300, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("luke_damageDown", "image/enemy/luke/damageDown.bmp", 450, 300, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("luke_knockDown", "image/enemy/luke/knockDown.bmp", 2100, 300, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("luke_knockUp", "image/enemy/luke/knockUp.bmp", 1200, 300, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("luke_jump", "image/enemy/luke/jump.bmp", 1500, 300, 10, 2, true, RGB(255, 0, 255));


	//dobeman
	IMAGEMANAGER->addFrameImage("dobeman_idle", "image/enemy/dobeman/idle.bmp", 800, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dobeman_attack", "image/enemy/dobeman/attack.bmp", 1800, 400, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dobeman_run", "image/enemy/dobeman/run.bmp", 1200, 400, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dobeman_damage", "image/enemy/dobeman/damage.bmp", 1000, 400, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dobeman_knockDown", "image/enemy/dobeman/knockDown.bmp", 2800, 400, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dobeman_knockUp", "image/enemy/dobeman/knockUp.bmp", 1000, 400, 5, 2, true, RGB(255, 0, 255));
}