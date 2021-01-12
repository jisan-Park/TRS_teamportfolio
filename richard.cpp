#include "stdafx.h"
#include "richard.h"

HRESULT richard::init(const char * imageName, float x, float y)
{
	return S_OK;
}

void richard::atk()
{
}

void richard::move()
{
}

void richard::update()
{
}

void richard::collsion()
{
}

void richard::inrange()
{
}

void richard::setAnimation()
{
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_IDLE_RIGHT", "richard_idle", 0, 3, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_IDLE_LEFT", "richard_idle", 7, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_LOBJ_IDLE_RIGHT", "richard_lobj_idle", 0, 3, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_LOBJ_IDLE_LEFT", "richard_lobj_idle", 7, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_HOBJ_IDLE_RIGHT", "richard_hobj_idle", 0, 3, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_HOBJ_IDLE_LEFT", "richard_hobj_idle", 7, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_RUN_RIGHT", "richard_run", 0, 5, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_RUN_LEFT", "richard_run", 11, 6, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_LOBJ_RUN_RIGHT", "richard_lobj_run", 0, 5, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_LOBJ_RUN_LEFT", "richard_lobj_run", 11, 6, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_HOBJ_RUN_RIGHT", "richard_hobj_run", 0, 5, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_HOBJ_RUN_LEFT", "richard_hobj_run", 11, 6, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_DAMAGE_RIGHT", "richard_damage", 0, 2, 8, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_DAMAGE_LEFT", "richard_damage", 5, 3, 8, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_DOWNDAMAGE_RIGHT", "richard_damageDown", 0, 2, 8, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_DOWNDAMAGE_LEFT", "richard_damageDown", 5, 3, 8, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_KNOCKDOWN_RIGHT", "richard_knockDown", 0, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_KNOCKDOWN_RIGHT", "richard_knockDown", 27, 14, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_KNOCKUP_RIGHT", "richard_knockUp", 0, 7, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_KNOCKUP_LEFT", "richard_knockUp", 15, 8, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_LOBJ_PICK_RIGHT", "richard_lobj_pick", 0, 2, 8, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_LOBJ_PICK_LEFT", "richard_lobj_pick", 5, 3, 8, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_HOBJ_PICK_RIGHT", "richard_hobj_pick", 0, 1, 8, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_HOBJ_PICK_LEFT", "richard_hobj_pick", 3, 2, 8, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_LOBJ_ATTACK_RIGHT", "richard_lobj_attack", 0, 4, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_LOBJ_ATTACK_LEFT", "richard_lobj_attack", 9, 5, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_HOBJ_ATTACK_RIGHT", "richard_hobj_attack", 0, 7, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("richard_HOBJ_ATTACK_LEFT", "richard_hobj_attack", 15, 8, 10, false, false);

}

void richard::rightAttack(void * obj)
{
}

void richard::leftAttack(void * obj)
{
}

void richard::rightdown(void * obj)
{
}

void richard::leftdown(void * obj)
{
}
