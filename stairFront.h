#pragma once
#include "line.h"
class stairFront :
	public line
{
public:
	virtual void collision(characterInfo &info);
};

