#pragma once
#define SHAKEPOWER 100
#define SIGHTSIZE 10

class camera
{
private:
	POINT pt;
	int _phase;
	bool _stop;

public:
	camera();
	~camera();

	//�ʱ�ȭ
	void init(float x, float y);
	//update
	void setCamera(float x, float y);
	void checkPoint();
	void update();

	//�þ� �̵��� �۵�
	void movePoint(float x, float y);

	//setter
	void setX(float x) { pt.x = x; };
	void setY(float y) { pt.y = y; };
	void setPhase(int i) { _phase = i; };
	//getter
	POINT getPoint() { return pt; };
	int getPhase() { return _phase; };
};
