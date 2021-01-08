#pragma once
#include "line.h"
class rightLine :
	public line
{
public:
	virtual void collison(characterInfo &info);
};

