#pragma once
#define SHAKEPOWER 100
#define SIGHTSIZE 10

class camera
{
private:
	POINT pt;

public:
	camera();
	~camera();

	//초기화
	void init(float x, float y);
	//update
	void setCamera(float x, float y);
	void checkPoint();

	//시야 이동시 작동
	void movePoint(float x, float y);
	//getter
	//render시 사용
	POINT getPoint();
};
