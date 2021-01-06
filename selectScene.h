#pragma once
#include "gameNode.h"
class selectScene: public gameNode
{
private:
	image* _scott;
	image* _ramona;

	animation* _scottMotion;
	animation* _ramonaMotion;

	image* _img;
	RECT _rc;
	int _selectPosition;

	bool _isChanged;
public:
	selectScene();
	~selectScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

