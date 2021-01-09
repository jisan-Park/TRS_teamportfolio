#pragma once
#include "line.h"
class leftLine :
	public line
{
public:
	virtual void collision(characterInfo &info);
};

