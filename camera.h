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

	//�ʱ�ȭ
	void init(float x, float y);
	//update
	void setCamera(float x, float y);
	void checkPoint();

	//�þ� �̵��� �۵�
	void movePoint(float x, float y);
	//getter
	//render�� ���
	POINT getPoint();
};
