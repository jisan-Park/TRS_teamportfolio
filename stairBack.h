#pragma once
#include "line.h"
class stairBack :
	public line
{
public:
	virtual void collision(characterInfo &info);
};

