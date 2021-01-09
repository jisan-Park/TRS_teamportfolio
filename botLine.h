#pragma once
#include "line.h"
class botLine :
	public line
{
public:
	virtual void collision(characterInfo &info);
};

