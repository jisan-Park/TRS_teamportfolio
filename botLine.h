#pragma once
#include "line.h"
class botLine :
	public line
{
public:
	virtual void collison(characterInfo &info);
};

