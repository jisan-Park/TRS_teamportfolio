#pragma once
#include "line.h"
class rightLine :
	public line
{
public:
	virtual void collision(characterInfo &info);
};

