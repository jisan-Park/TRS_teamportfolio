#pragma once
#include "line.h"
class baricadeLine :
	public line
{
public:
	virtual void collision(characterInfo &info);
};
