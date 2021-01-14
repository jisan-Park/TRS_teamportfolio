#pragma once
#include "gameNode.h"
#include "bat.h"
#include "bin.h"
#include <vector>
class ioManager :
	public gameNode
{
private:
	typedef vector<interactiveObject*>vIO;
	typedef vector<interactiveObject*>::iterator viIO;

private:
	vIO _vIO;
	viIO _viIO;
public:
	ioManager();
	~ioManager();
	HRESULT init();
	void release();
	void update();
	void setBat();
	void setBin();


	void setImage();

	void render();

	inline vIO getVIO() { return _vIO; };

};

