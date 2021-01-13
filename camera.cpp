#include "stdafx.h"
#include "camera.h"
using namespace std;

camera::camera()
{
}
camera::~camera()
{
}
//들어온 것은 이미지의 left top
void camera::init(float x, float y) {
	//Scene 시작 시에만 호출
	_phase = -1;
	_stop = false;
	pt.x = x;
	pt.y = y;
}
void camera::setCamera(float x, float y) {
	//카메라 고정상태면 x축 고정 y만 이동
	if (_stop) {
		pt.y = y;
	}
	else {
		pt.x = x;
		pt.y = y;
	}
}

//phase 에 따른 camera stop (고정)
void camera::checkPoint()
{
	//x 가 333이상이고, phase 1보다 낮으면
	if (pt.x >= 333 && _phase < 1) {
		_phase = 1;
		setX(333);
		_stop = true;
	}
	//x 가 1610이상이고, phase 3보다 낮으면
	if (pt.x >= 1610 && _phase < 3) {
		_phase = 3;
		setX(1610);
		_stop = true;
	}
	//x 가 3880이상이고, phase 5보다 낮으면
	if (pt.x >= 3880 && _phase < 5) {
		_phase = 5;
		setX(3880);
		_stop = true;
	}
	//x 가 5500이상이고, phase 7보다 낮으면
	if (pt.x >= 5500 && _phase < 7) {
		_phase = 7;
		setX(5500);
		_stop = true;
	}
	//x 가 6980이상이고, phase 9보다 낮으면
	if (pt.x >= 6980 && _phase < 9) {
		_phase = 9;
		setX(6980);
		_stop = true;
	}
	//x 가 8615이상이고, phase 11보다 낮으면
	if (pt.x >= 8615 && _phase < 11) {
		_phase = 11;
		setX(8615);
		_stop = true;
	}
	//x 가 9430이상이고, phase 13보다 낮으면
	if (pt.x >= 9430 && _phase < 13) {
		_phase = 13;
		setX(9430);
		_stop = true;
	}
	//x 가 15645이상이고, phase 15보다 낮으면
	if (pt.x >= 15645 && _phase < 15) {
		_phase = 15;
		setX(15645);
		_stop = true;
	}
	//x 가 17514이상이고, phase 17보다 낮으면
	if (pt.x >= 17514 && _phase < 17) {
		_phase = 17;
		setX(17514);
		_stop = true;
	}
	//x 가 19562이상이고, phase 19보다 낮으면
	if (pt.x >= 19562 && _phase < 19) {
		_phase = 19;
		setX(19562);
		_stop = true;
	}
}
//페이즈 관계없이 맵에 카메라 예외처리 (막기)
void camera::update()
{
	//ingame아니면 0,0 고정
	if (_phase == -1 || _phase > 21) {
		setCamera(0, 0);
	}
	if (_phase % 2 == 0) {
		//짝수면 camera 고정 풀어주기
		_stop = false;
	}
	//보스방 들어가기 전이면(0~20)
	if (_phase <= 20) {
		//x축 보정
		if (pt.x < 20) {
			pt.x = 20;
		}
		if (pt.x > 21228 - WINSIZEX) {
			pt.x = 21228 - WINSIZEX;
		}
		//y축 보정
		if (pt.y < 60) {
			pt.y = 60;
		}
		//터널전 
		if (pt.x < 16452) {
			if (pt.y > MAPSIZEY - WINSIZEY - 126) {
				pt.y = MAPSIZEY - WINSIZEY - 126;
			}
		}//터널 이후 대각선 
		else if (pt.x < 16500) {
			if (pt.y > MAPSIZEY - WINSIZEY - 114) {
				pt.y = MAPSIZEY - WINSIZEY - 114;
			}
		}
		else if (pt.x < 16600) {
			if (pt.y > MAPSIZEY - WINSIZEY - 100) {
				pt.y = MAPSIZEY - WINSIZEY - 100;
			}
		}
		else if (pt.x < 16700) {
			if (pt.y > MAPSIZEY - WINSIZEY - 80) {
				pt.y = MAPSIZEY - WINSIZEY - 80;
			}
		}
		else if (pt.x < 16800) {
			if (pt.y > MAPSIZEY - WINSIZEY - 60) {
				pt.y = MAPSIZEY - WINSIZEY - 60;
			}
		}
		else if (pt.x < 16900) {
			if (pt.y > MAPSIZEY - WINSIZEY - 40) {
				pt.y = MAPSIZEY - WINSIZEY - 40;
			}
		}
		else if (pt.x < 17000) {
			if (pt.y > MAPSIZEY - WINSIZEY - 20) {
				pt.y = MAPSIZEY - WINSIZEY - 20;
			}
		}
		else {
			if (pt.y > MAPSIZEY - WINSIZEY - 14) {
				pt.y = MAPSIZEY - WINSIZEY - 14;
			}
		}
	}
	else {
		//보스방 예외처리
		if (pt.x <= 21268) {
			pt.x = 21268;
		}
		if (pt.x >= 22212) {
			pt.x = 22212;
		}
		if (pt.y <= 162) {
			pt.y = 162;
		}
		if (pt.y >= 730) {
			pt.y = 730;
		}
	}

}

void camera::movePoint(float x, float y)
{
	this->pt.x += x;
	this->pt.y += y;
}